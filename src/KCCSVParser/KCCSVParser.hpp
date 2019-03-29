//@KCLIB_FILE_COMMENT
#pragma once

#include <utility>
#include <string>
#include <sstream>
#include <tuple>
#include <fstream>
#include <vector>

namespace KC
{
	template<class T>
	auto ExtractValueFromString(std::string const& data);

	template <>
	auto ExtractValueFromString<int>(std::string const& data)
	{
		return std::stoi(data);
	}
	template <>
	auto ExtractValueFromString<double>(std::string const& data)
	{
		return std::stod(data);
	}
	template <>
	auto ExtractValueFromString<float>(std::string const& data)
	{
		return std::stof(data);
	}
	template <>
	auto ExtractValueFromString<char>(std::string const& data)
	{
		return data[0];
	}
	template<>
	auto ExtractValueFromString<std::string>(std::string const& data)
	{
		return data;
	}

	struct CSVEndOfFileException : std::exception
	{
		using std::exception::what;
		CSVEndOfFileException() : std::exception("CSV Parser Error: End of file encountered unexpectedly") { }
	};

	struct CSVFileNotFoundException : std::exception
	{
		using std::exception::what;
		CSVFileNotFoundException() : std::exception("CSV Parser Error: File not found") { }
	};

	template<class ...Types>
	class CSVParser
	{
		using Data = std::tuple<Types...>;

		std::string const fileName;
		std::ifstream dataFile{};
		int const defaultLinesToSkip = 0;

		char delim{','};

	public:
		CSVParser(std::string const& fileName, int const linesToSkip = 0) : fileName{fileName}, dataFile{fileName}, defaultLinesToSkip(linesToSkip)
		{
			if(!dataFile.is_open())
			{
				throw CSVFileNotFoundException{};
			}
			SkipLines(defaultLinesToSkip);
		}

		void ResetFile()
		{
			dataFile.close();
			dataFile.open(fileName);
		}

		void SkipLines(int const linesToSkip)
		{
			for (auto i = 0; i < linesToSkip; i++)
			{
				std::getline(dataFile,std::string{},'\n');
			}
		}

		void SetDelim(char const c)
		{
			delim = c;
		}

	private:
		// adapted from https://en.cppreference.com/w/cpp/utility/integer_sequence
		template<std::size_t... I>
		auto v2t_impl(const std::vector<std::string>& a, std::index_sequence<I...>)
		{
			return std::make_tuple(ExtractValueFromString<Types>(a[I])...);
		}
		template<std::size_t N, typename Indeces = std::make_index_sequence<N>>
		auto v2t(const std::vector<std::string>& a)
		{
			return v2t_impl(a, Indeces{});
		}

	public: 
		auto ReadLine()
		{
			if(dataFile.eof())
			{
				throw CSVEndOfFileException{};
			}
			Data d;
			std::string line;
			std::getline(dataFile,line,'\n');
			std::stringstream lineStream{line};

			std::vector<std::string> dataArray;
			for (auto i = 0; i < sizeof...(Types); i++)
			{
				std::string dataValue{};
				std::getline(lineStream,dataValue,delim);
				dataArray.push_back(dataValue);
			}

			return v2t<sizeof...(Types)>(dataArray);
		}

		auto ReadLine(Data& d)
		{
			d = ReadLine();
			return d;
		}

		auto ReadFile()
		{
			ResetFile();
			SkipLines(defaultLinesToSkip);

			std::vector<Data> dataList;
			try
			{
				while(true)
				{
					dataList.push_back(ReadLine());
				}
			} catch(CSVEndOfFileException&){}

			return dataList;
		}

		auto ReadFile(std::vector<Data>& vd)
		{
			vd = ReadFile();
			return vd;
		}

		~CSVParser()
		{
			dataFile.close();
		}


	};
}
