//@KCLIB_FILE_COMMENT
#pragma once

#include <Windows.h>
#include <string>

namespace KC
{
	namespace Music
	{
		static const int TONE_VALUE[58] = {
			16, 18, 20, 21, 24, 27, 30, 32, 36, 41, 43, 49, 55, 61, 65, 73, 82, 87, 98, 110, 123, 130, 146, 164, 174,
			196, 220, 246, 261, 293, 329, 349, 392, 440, 493, 523, 587, 659, 698, 783, 880, 987, 1046, 1174, 1318, 1396,
			1567, 1760, 1975, 2093, 2349, 2637, 2793, 3135, 3520, 3951, 4186, 4698
		};

		static int FetchTone(int const row, int const column, int const noteOffset = 0)
		{
			if (!noteOffset)
			{
				return TONE_VALUE[(row + (column < 'C')) * 7 + column - 'A' - 2];
			}
			return FetchTone(row, column) + (FetchTone(row, column + noteOffset) - FetchTone(row, column)) / 2;
		}

		enum class NoteLength : char
		{
			Whole = 'W',
			Half = 'H',
			Quarter = 'Q',
			Eighth = 'E'
		};
	}

	class MusicFile final
	{
		static void TestFileParsing(const bool& fileStart, const bool& fileEnd, const bool& musicStart,
		                            const int& bpm, const int& baseNote);
		static int ConvertNoteToIndex(const Music::NoteLength& n);
		static void PlayNote(int noteTone, DWORD duration, DWORD sleepMilliseconds);
		void SetLocals(const std::stringstream& buffer, const int& bpm, const int& baseNote);

		std::string Buffer;
		int WholeNoteDuration;
		int HalfNoteDuration;
		int QuarterNoteDuration;
		int EighthNoteDuration;
	public:
		static void PlayString(std::string& buffer, int timeInBetweenNotes);
		MusicFile() = delete;
		explicit MusicFile(const std::string& filename);
		explicit MusicFile(std::string&& filename);
		void ParseMusicFile(const std::string& fileName);
		void Play(DWORD timeToWaitInBetweenNotes = 0) const;
	};
}