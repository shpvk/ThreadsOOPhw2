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

		while (!file.eof())
		{
			string buff;
			getline(file, buff);
			lineCount++;
			cout << buff << endl;
		}
		flag.unlock();

		

		flag.lock();
		
		char c;
		while (file.get(c))
		{
			charCount++;
		};

		flag.unlock();
		
		flag.lock();
		while (file.get(c))
		{
			if (c == ' ')
			{
				wordCount++;
			}
		}
		flag.unlock();
	}

	void Save(string filename)
	{

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
		file(filename, ios::app)
	{

	}
	
	void Write(string text)
	{
		file << text;
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
	thread t1(WordCounter::Read, &reader, file.GetFileName());
	
	t1.join();



	cout << "Char count = " << reader.GetCharCount() << endl;
	cout << "Line count = " << reader.GetLineCount() << endl;
	cout << "Word count = " << reader.GetWordCount() << endl;
	//thread read(reader.Read(obj.GetFileName()));
}