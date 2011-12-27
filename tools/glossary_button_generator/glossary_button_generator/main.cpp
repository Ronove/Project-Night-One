#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "CSVReader.hpp"

struct DatasetEntry
{
	DatasetEntry(const std::string& input_string, const std::string& output_filename)
		: input_string(input_string), output_filename(output_filename){}
	std::string input_string;
	std::string output_filename;
};

template<class RectTypeA, class RectTypeB>
sf::Vector2f center_A_in_B(const RectTypeA& a, const RectTypeB& b)
{
	return sf::Vector2f(b.Width/2.0f - a.Width/2.0f, b.Height/2.0f - a.Height/2.0f);
}

int main()
{
	try
	{
		// --- FONT ---
		// read font name from file
		std::ifstream font_name_file("data/font.txt");
		if(!font_name_file)
		{
			throw std::string("Could not open data/font.txt");
		}
		std::string font_name;
		font_name_file >> font_name;
		font_name_file.close();
		// read font point size
		int font_size;
		std::ifstream font_size_file("data/fontsize.txt");
		if(!font_size_file)
		{
			throw std::string("Could not open data/fontsize.txt");
		}
		font_size_file >> font_size;
		font_size_file.close();
		// create sf::Font object and load the given font
		sf::Font text_font;
		if(!text_font.LoadFromFile("data/" + font_name))
		{
			throw std::string("Could not load font: data/") + font_name;
		}

		// --- DATASET ---
		// open dataset file
		CSVReader csv_reader;
		csv_reader.openFile("data/dataset.csv");
		if(!csv_reader.isOpened())
		{
			throw std::string("Could not open data/dataset.csv");
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

		sf::Texture button_template_tex;
		if(!button_template_tex.LoadFromFile("data/button_template.bmp"))
		{
			throw std::string("Could not open template imate: data/button_template.bmp");
		}
		sf::Sprite button_template(button_template_tex);

		const int kBUTTON_WIDTH = button_template_tex.GetWidth()/4;
		const int kBUTTON_HEIGHT = button_template_tex.GetHeight();
		const sf::FloatRect kBUTTON_RECT(0.0f,0.0f,static_cast<float>(kBUTTON_WIDTH),static_cast<float>(kBUTTON_HEIGHT));

		// --- WINDOW ---
		// create window upon which the images will be previewed
		sf::RenderWindow window;
		window.Create(sf::VideoMode(button_template_tex.GetWidth(),button_template_tex.GetHeight(),32),"Higanbana glossary button generator");
		if(!window.IsOpened())
		{
			throw std::string("Failed to open render window");
		}

		// --- SHADER ---
		// sfml does not support outlined text by default, so I used a glsl script from this thread: http://www.sfml-dev.org/forum/viewtopic.php?p=22673&sid=16f1b4662050f692d4f5e1a47cb31e93
		sf::Shader shader;
		if(!shader.LoadFromFile("data/outlineshader.glsl"))
		{
			throw std::string("Failed to open file data/outlineshader.glsl");
		}
		if(!shader.IsAvailable())
		{
			std::cout << "WARNING: Your system does not support the outline shader. Are you running this on a potato?" << std::endl;
		}

		// process each entry
		for(unsigned i = 0; i < data_entries.size(); ++i)
		{
			window.Clear();

			// draw background
			window.Draw(button_template);

			// Create graphical string
			sf::String string_to_render(data_entries[i].input_string);
			sf::Text text(string_to_render,text_font,font_size);

			// render the text onto a texture in order to apply teh shaders on it
			text.SetColor(sf::Color::White);
			sf::RenderTexture render_texture;
			render_texture.Create(static_cast<unsigned>(kBUTTON_RECT.Width),static_cast<unsigned>(kBUTTON_RECT.Height));
			// center text on render texture
			text.SetPosition(center_A_in_B(text.GetRect(),kBUTTON_RECT));
			render_texture.Draw(text);
			render_texture.Display();
			const sf::Texture& texture(render_texture.GetTexture());

			// set shader attributes
			shader.SetTexture("tex",texture);
			shader.SetParameter("texSize",static_cast<float>(render_texture.GetWidth()), static_cast<float>(render_texture.GetHeight()));
			shader.SetParameter("outlineColor", 0,0,0,1);

			// bind shader
			shader.Bind();

			// create sprite from text texture to be able to draw it
			sf::Sprite text_sprite(texture);

			// center text to first button
			text_sprite.SetPosition( center_A_in_B( sf::FloatRect(sf::Vector2f(),text_sprite.GetSize()), kBUTTON_RECT ));
			window.Draw(text_sprite,shader);
			// move text two buttons to the right
			text_sprite.Move(sf::Vector2f(kBUTTON_WIDTH*2.0f,0));
			window.Draw(text_sprite,shader);

			// unbind texture
			shader.Unbind();

			sf::Image screenshot = window.Capture();
			if(!screenshot.SaveToFile(data_entries[i].output_filename))
			{
				std::cerr << "You can't save images in non-existant directories. Does the directory you tried to save to need to be created?" << std::endl;
			}
			else
			{
				std::cout << "Created " << data_entries[i].output_filename << " from " << data_entries[i].input_string << std::endl;
			}

			window.Display();
		}
	}
	catch(std::string error_message)
	{
		std::cout << "Hint generator failed with error: " << std::endl << error_message << std::endl;
	}
}
