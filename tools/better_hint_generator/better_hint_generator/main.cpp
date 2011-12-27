#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "CSVReader.hpp"

// constants
#define IMAGE_WIDTH 472
#define IMAGE_HEIGHT 386
#define PAGE_RECT sf::IntRect(0,0,IMAGE_WIDTH/2,IMAGE_HEIGHT)
#define TEXT_OFFSET sf::Vector2i(18,73)

struct DatasetEntry
{
	DatasetEntry(const std::string& input_filename, const std::string& output_filename)
		: input_filename(input_filename), output_filename(output_filename){}
	std::string input_filename;
	std::string output_filename;
};

int main()
{
	try
	{
		// --- FONT ---
		// read font name from file
		std::ifstream font_name_file("config/font.txt");
		if(!font_name_file)
		{
			throw std::string("Could not open config/font.txt");
		}
		std::string font_name;
		font_name_file >> font_name;
		font_name_file.close();
		// read font point size
		int font_size;
		std::ifstream font_size_file("config/fontsize.txt");
		if(!font_size_file)
		{
			throw std::string("Could not open config/fontsize.txt");
		}
		font_size_file >> font_size;
		font_size_file.close();
		// create sf::Font object and load the given font
		sf::Font text_font;
		if(!text_font.LoadFromFile("font/" + font_name))
		{
			throw std::string("Could not load font: font/") + font_name;
		}

		// --- DATASET ---
		// open dataset file
		CSVReader csv_reader;
		csv_reader.openFile("config/dataset.csv");
		if(!csv_reader.isOpened())
		{
			throw std::string("Could not open config/dataset.csv");
		}
		// parse dataset and add it to a data structure
		std::vector<DatasetEntry> data_entries;
		for(int i = 1; csv_reader.hasMoreRows(); ++i)
		{
			std::vector<std::string> row = csv_reader.getRow();
			if(row.size() < 2 || row.size() > 3)
			{
				std::stringstream ss;
				ss << "Invalid number of entries in row number " << i << " in dataset.csv." << std::endl;
				ss << "Expects 2 entries per line, but got " << row.size() << std::endl;
				ss << "The infringing line's contents were: " << std::endl;
				for(unsigned j = 0; j < row.size(); ++j)
				{
					ss << "Entry " << j+1 << ": " << row[j] << std::endl;
				}
				ss << std::endl;
				throw std::string(ss.str());
			}
			data_entries.push_back(DatasetEntry(row[0],row[1]));
		}
		csv_reader.closeFile();

		// --- WINDOW ---
		// create window upon which the images will be previewed
		sf::RenderWindow window;
		window.Create(sf::VideoMode(IMAGE_WIDTH,IMAGE_HEIGHT,32),"Higanbana better hint generator");
		if(!window.IsOpened())
		{
			throw std::string("Failed to open render window");
		}

		// make sure the window is opened properly... this is an attempted fix at a bug.
		while(!window.IsOpened());

		// --- SHADER ---
		// sfml does not support outlined text by default, so I used a glsl script from this thread: http://www.sfml-dev.org/forum/viewtopic.php?p=22673&sid=16f1b4662050f692d4f5e1a47cb31e93
		sf::Shader shader;
		if(!shader.LoadFromFile("config/outlineshader.glsl"))
		{
			throw std::string("Failed to open file config/outlineshader.glsl");
		}
		if(!shader.IsAvailable())
		{
			std::cout << "WARNING: Your system does not support the outline shader. Are you running this on a potato?" << std::endl;
		}

		// --- PROCESSING ---
		// create the two rectangles which represent the white/black halves
		sf::Shape black_half, white_half;
		black_half = sf::Shape::Rectangle(static_cast<sf::FloatRect>(PAGE_RECT),sf::Color(sf::Color::Black));
		white_half = sf::Shape::Rectangle(static_cast<sf::FloatRect>(PAGE_RECT),sf::Color(sf::Color::White));
		white_half.SetPosition(IMAGE_WIDTH/2,0);
		for(unsigned i = 0; i < data_entries.size(); ++i)
		{
			window.Clear();
			
			// render black and white background
			window.Draw(black_half);
			window.Draw(white_half);

			// open file for text to render
			std::ifstream input_text("input/" + data_entries[i].input_filename);
			if(!input_text)
			{
				std::stringstream ss;
				ss << "Could not open file for reading: input/" << data_entries[i].input_filename;
				throw ss.str();
			}
			std::stringstream input_sstream;
			input_sstream << input_text.rdbuf();
			std::string input_string = input_sstream.str();

			// LEFT IMAGE
			{
				sf::String string_to_render(input_string);
				sf::Text text(string_to_render,text_font,font_size);

				// prepare text at left position
				text.SetPosition(static_cast<sf::Vector2f>(TEXT_OFFSET));
				text.SetColor(sf::Color::White);

				// draw text at left position
				window.Draw(text);
			}
			// RIGHT IMAGE
			{
				sf::String string_to_render(input_string);
				sf::Text text(string_to_render,text_font,font_size);

				// render the text onto a texture in order to apply teh shaders on it
				text.SetColor(sf::Color::Black);
				sf::RenderTexture render_texture;
				render_texture.Create(IMAGE_WIDTH/2,IMAGE_HEIGHT);
				render_texture.Draw(text);
				render_texture.Display();
				const sf::Texture& texture(render_texture.GetTexture());

				// set shader attributes
				shader.SetTexture("tex",texture);
				shader.SetParameter("texSize",static_cast<float>(render_texture.GetWidth()), static_cast<float>(render_texture.GetHeight()));
				shader.SetParameter("outlineColor", 0,0,0,1);
				
				shader.Bind();
				
				// create sprite from text texture to be able to draw it
				sf::Sprite text_sprite(texture);

				// move text to right position
				text_sprite.SetPosition(static_cast<sf::Vector2f>(TEXT_OFFSET));
				text_sprite.Move(sf::Vector2f(IMAGE_WIDTH/2,0));

				window.Draw(text_sprite,shader);
				shader.Unbind();
			}
			// capture an image of the screen
			sf::Image screencap = window.Capture();

			// save to appropriate place
			std::cout << "Created image output/" << data_entries[i].output_filename << " from input/" << data_entries[i].input_filename << std::endl;
			if(!screencap.SaveToFile("output/" + data_entries[i].output_filename))
			{
				std::cout << "Does the folder exist? If not, you must create it." << std::endl;
			}
			window.Display();
		}

	}
	catch(std::string error_message)
	{
		std::cout << "Hint generator failed with error: " << std::endl << error_message << std::endl;
	}
}
