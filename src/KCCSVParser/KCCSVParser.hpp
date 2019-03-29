//@KCLIB_FILE_COMMENT
#pragma once

#include <utility>
#include <sstream>
#include <string>
#include <tuple>
#include <fstream>
#include <vector>
#include <iostream>

namespace KC
{
	template<class T>
	auto ExtractValueFromString(std::string const& data);

	template <>
	inline auto ExtractValueFromString<int>(std::string const& data)
	{
		return std::stoi(data);
	}
	template <>
	inline auto ExtractValueFromString<double>(std::string const& data)
	{
		return std::stod(data);
	}
	template <>
	inline auto ExtractValueFromString<float>(std::string const& data)
	{
		return std::stof(data);
	}
	template <>
	inline auto ExtractValueFromString<char>(std::string const& data)
	{
		return data[0];
	}
	template<>
	inline auto ExtractValueFromString<std::string>(std::string const& data)
	{
		return data;
	}

	struct CSVEndOfFileException final : std::exception
	{
		using std::exception::what;
		CSVEndOfFileException() : std::exception("CSV Parser Error: End of file encountered unexpectedly") { }
	};

	struct CSVFileNotFoundException final : std::exception
	{
		using std::exception::what;
		CSVFileNotFoundException() : std::exception("CSV Parser Error: File not found") { }
	};

	template<class ...Types>
	class CSVParser final
	{
		using Data = std::tuple<Types...>;

		std::string const FileName;
		std::ifstream DataFile{};
		int const DefaultLinesToSkip = 0;

		char Delimiter{','};

	public:
		explicit CSVParser(std::string const& fileName, int const linesToSkip = 0) : FileName{fileName}, DataFile{fileName}, DefaultLinesToSkip(linesToSkip)
		{
			if(!DataFile.is_open())
			{
				throw CSVFileNotFoundException{};
			}
			SkipLines(DefaultLinesToSkip);
		}

		void ResetFile()
		{
			DataFile.close();
			DataFile.open(FileName);
		}

		void SkipLines(int const linesToSkip)
		{
			for (auto i = 0; i < linesToSkip; i++)
			{
				std::getline(DataFile,std::string{},'\n');
			}
		}

		void SetDelimiter(char const c)
		{
			Delimiter = c;
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
			if(DataFile.eof())
			{
				throw CSVEndOfFileException{};
			}
			Data d;
			std::string line;
			std::getline(DataFile,line,'\n');
			std::stringstream lineStream{line};

			std::vector<std::string> dataArray;
			for (auto i = 0; i < sizeof...(Types); i++)
			{
				std::string dataValue{};
				std::getline(lineStream,dataValue,Delimiter);
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
			SkipLines(DefaultLinesToSkip);

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

		void CloseFile() 
		{
			try
			{
				DataFile.close();
			} catch (std::fstream::failure const& e)
			{
				std::cerr << "Error while closing file: " << e.what();
			}
		}

		~CSVParser()
		{
			CloseFile();
		}
	};
}
