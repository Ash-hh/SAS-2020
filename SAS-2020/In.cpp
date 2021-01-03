#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>

#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"


namespace In
{
	IN getin(wchar_t infile[])
	{
		setlocale(LC_ALL, "rus");
		IN in;

		in.size = 0;
		in.text = new char[IN_MAX_LEN_TEXT];		
		in.lines = 0;		
		in.ignor = 0;		

		std::ifstream file(infile);
		std::string line;

		
		int blockcounter = 0;		
		int hesiscounter = 0;
		bool isline = false;
		unsigned char ltr,bltr =' ';
		
		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file, line);
				in.lines++;
				
				for (int i=0; i < line.length(); i++)
				{				
					ltr = line[i];
					switch (in.code[ltr])
					{
					case IN::F: throw ERROR_THROW_IN(111, in.lines, i); break;
					case IN::I: in.ignor++; break;
					case IN::S: 
						switch (ltr)
						{
						case '(': hesiscounter++; break;
						case ')': if (--hesiscounter < 0)
							throw ERROR_THROW_IN(106, in.lines,i); break;
						case '{': blockcounter++;  break;
						case '}': if (--blockcounter < 0)
						{
							std::cout << in.lines;
							throw ERROR_THROW_IN(107, in.lines, i);  break;
						}
							
						}
						if (bltr != ' ' && bltr!='|')
						{
							in.text[in.size] = ' ';
							in.size++;
						}							
								in.text[in.size] = line[i];
								in.text[++in.size] = ' ';
								in.size++;
								bltr = ' ';
						break;
					case IN::T:	
						
						if ((int)ltr == 39)
						{
							if (isline == false)
								isline = true;
							else
								isline = false;
						}


						if (line[i] == bltr && bltr == ' ' && isline==false)
						{
							break;
						}
						else
						{								
							in.text[in.size] = line[i];
							bltr = line[i];
							in.size++;
							break;
						}									

					default: ltr = in.code[ltr]; 
						in.text[in.size] = ltr;
						in.size++;
						break;						
					}
				}	
				if (bltr != ' ')
				{
					in.text[in.size++] = ' ';
					in.text[in.size++] = IN_CODE_ENDL; 
					bltr = '|';
				}
				else
				{
					in.text[in.size] = IN_CODE_ENDL; in.size++;
					bltr = '|';
				}
				
			}
			in.text[in.size-1] = '\0';

			if (isline)
			{
				throw ERROR_THROW(105);
			}
			if (blockcounter > 0)
			{
				throw ERROR_THROW(107);
			}
			if (hesiscounter > 0)
			{
				throw ERROR_THROW(106);
			}
		}
		else
		{
			throw ERROR_THROW(110);
		}	

		file.close();	

		return in;
	}

	int words(char* text)
	{
		int i = 0;
		int k = 0;
		int size = 0;
		if (text[0] != ' ')
			k++;
		while (text[i] != '\0')
		{
			size++;
			if (text[i] == ' ')
				k++;
			i++;
		}
		if (text[size-1] == ' ')
			k--;
		return k;
	}
	
	void FileOut(wchar_t outfile[], IN in)
	{
		std::ofstream fout(outfile);
		int i =0;
		while (in.text[i]!='\0')
		{			
			fout << in.text[i];
			if (in.text[i] == IN_CODE_ENDL)
			{
				fout << '\n';
			}
			i++;
		}
		

		delete in.text;

		fout.close();
	}

}