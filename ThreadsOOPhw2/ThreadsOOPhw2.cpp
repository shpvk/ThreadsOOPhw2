#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>

using namespace std;
mutex flag;

class WordCounter
{
private:
	int charCount;
	int wordCount;
	int lineCount;
public:
	WordCounter()
	{
		this->charCount = 0;
		this->wordCount = 0;
		this->lineCount = 0;
	}
	void Read(string filename)
	{
		flag.lock();
		ifstream file(filename);
		string line;
		while (getline(file, line))
		{
			lineCount++;
			charCount += int(line.size());

			bool isWord = false;
			for (int i = 0; i < line.size(); ++i)
			{
				if (!isspace(line[i]))
				{
					if (!isWord)
					{
						wordCount++;
						isWord = true;
					}
				}
				else
				{
					isWord = false;
				}
			}
			cout << line << endl;
		}
		flag.unlock();

	}
	int GetCharCount()
	{
		return this->charCount;
	}

	int GetWordCount()
	{
		return this->wordCount;
	}

	int GetLineCount()
	{
		return this->lineCount;
	}


};

class CreateFile
{
private:
	string filename;
	ofstream file;

public:
	CreateFile() :
		filename("filename.txt"),
		file(filename, ios::app) { }
	
	void Write(string text)
	{
		file << text << endl;
	}

	string GetFileName()
	{
		return filename;
	}
};


int main()
{

	CreateFile file;

	string text;
	getline(cin, text);
	file.Write(text);

	WordCounter reader;
	thread t1(&WordCounter::Read, &reader, file.GetFileName());
	
	t1.join();

	cout << "Char count = " << reader.GetCharCount() << endl;
	cout << "Line count = " << reader.GetLineCount() << endl;
	cout << "Word count = " << reader.GetWordCount() << endl;
}