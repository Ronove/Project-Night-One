===============================
CREATING NEW GLOSSARY ENTRIES
===============================

A glossary entry is composed of two elements:
- An image for the button to click to read the glossary entry
- An image for the glossary entry itself

To create a new glossary entry, take the following steps:
1. Creating the button graphic
	a) Go to Project-Night-One\tools\glossary_button_generator\Release\data
	b) Open dataset.csv in a plain text editor (not Open Office Calc or Microsoft Excel)
	c) Add an entry to create a button. The format is "button name,output/my_button.bmp,"
		Remember the name you used to replace "my_button", it will be used later.

2. Creating the glossary page graphic
	a) Go to Project-Night-One\tools\better_hint_generator\Release\input\glossary
	b) Create a new text file, and write the glossary entry in it. (You may use Japanese symbols if you save the file with UTF-8 encoding)
	c) Go to Project-Night-One\tools\better_hint_generator\Release\config
	d) Open dataset.csv in a plain text editor (not Open Office Calc or Microsoft Excel)
	e) Add a new entry. The format is "glossary/your_filename.txt,glossary/my_glossary_entry.bmp,"
		Remember the name you used to replace "my_glossary_entry", it will be used later.

3. Adding the button and image into the automatically generated glossary script
	a) Go to Project-Night-One\tools\glossary_generator\bin
	b) Open dataset.csv in a plain text editor (not Open Office Calc or Microsoft Excel)
	c) Add a new entry. The format is "bmp\glos_btn\my_button.bmp,bmp\r_click\text\glos\my_glossary_entry.bmp,"

The next time you run "make_all.bat", it will all be put together and hopefully everything goes fine.
If there are problems, send an e-mail to nicolasg@uvic.ca

===============================
UNLOCKING GLOSSARY ENTRIES FROM THE SCRIPT
===============================

Glossary entries are unlocked sequentially (in linear order).
The current number of unlocked entries is stored in the variable EN_glossary_progress.

When you want to unlock an entry, insert the following into the script:

if %EN_glossary_progress > 2 jumpf
	mov %EN_glossary_progress,2
~

This will unlock the first 2 glossary entries, if they have not already been unlocked (important for re-reading).
To unlock up to the n-th glossary entry, where "n" is the number of entries you want to unlock
replace both occurrences of 2 in the sample of code with your number n

example: Unlocking the first 4 glossary entries

if %EN_glossary_progress > 4 jumpf
	mov %EN_glossary_progress,4
~

This might seem simple, but it would not be very surprising if a bug sneaks in due to human error.
Therefore, I recommend that QA makes sure glossary entires are properly being unlocked...

If there are any problems, send an e-mail to nicolasg@uvic.ca

***************
Added note:
***************
Glossary text color is currently: #ECD672 (Light Gold)
Sound entry code is: se1v 1011,50
