#include "KCMusic.hpp"
#include <fstream>
#include <sstream>
#include <locale>
#include <stdexcept>

using KC::Music::FetchTone;
using KC::Music::TONE_VALUE;
using KC::Music::NoteLength;

auto KC::MusicFile::TestFileParsing(const bool& fileStart, const bool& fileEnd, const bool& musicStart,
                                    const int& bpm, const int& baseNote) -> void
{
    if (!fileStart)
    {
        throw std::logic_error("ERROR: No 00 marker!");
    }
    if (bpm == 0)
    {
        throw std::logic_error("ERROR: No tempo set!");
    }
    if (baseNote == 0)
    {
        throw std::logic_error("ERROR: No base note set!");
    }
    if (!musicStart)
    {
        throw std::logic_error("ERROR: No M0 marker!");
    }
    if (!fileEnd)
    {
        throw std::logic_error("ERROR: No FF marker!");
    }
}

auto KC::MusicFile::ConvertNoteToIndex(const NoteLength& n) -> int
{
    switch (n)
    {
    case NoteLength::Whole:
        return 0;
    case NoteLength::Half:
        return 1;
    case NoteLength::Quarter:
        return 2;
    case NoteLength::Eighth:
        return 3;
    }
    return -1;
}

auto KC::MusicFile::PlayNote(const int noteTone, const DWORD duration, const DWORD sleepMilliseconds) -> void
{
    Beep(noteTone, duration);
    if (!sleepMilliseconds)
    {
        Sleep(sleepMilliseconds);
    }
}

auto KC::MusicFile::SetLocals(const std::stringstream& buffer, const int& bpm, const int& baseNote) -> void
{
    Buffer = buffer.str();
    switch (static_cast<NoteLength>(baseNote))
    {
    case NoteLength::Whole:
        WholeNoteDuration = 60 * 1000 / bpm;
        HalfNoteDuration = 60 * 1000 / 2 / bpm;
        QuarterNoteDuration = 60 * 1000 / 4 / bpm;
        EighthNoteDuration = 60 * 1000 / 8 / bpm;
        break;
    case NoteLength::Half:
        WholeNoteDuration = 60 * 1000 * 2 / bpm;
        HalfNoteDuration = 60 * 1000 / bpm;
        QuarterNoteDuration = 60 * 1000 / 2 / bpm;
        EighthNoteDuration = 60 * 1000 / 4 / bpm;
        break;
    case NoteLength::Quarter:
        WholeNoteDuration = 60 * 1000 * 4 / bpm;
        HalfNoteDuration = 60 * 1000 * 2 / bpm;
        QuarterNoteDuration = 60 * 1000 / bpm;
        EighthNoteDuration = 60 * 1000 / 2 / bpm;
        break;
    case NoteLength::Eighth:
        WholeNoteDuration = 60 * 1000 * 8 / bpm;
        HalfNoteDuration = 60 * 1000 * 4 / bpm;
        QuarterNoteDuration = 60 * 1000 * 2 / bpm;
        EighthNoteDuration = 60 * 1000 / bpm;
        break;
    default:
        throw std::logic_error("Base NoteLength is invalid!");
    }
    if (Buffer.length() == 0)
    {
        throw std::logic_error("Buffer remained unset!");
    }
}

void KC::MusicFile::PlayString(std::string& buffer, const int timeInBetweenNotes = 0)
{
    std::ofstream outfile("temp.music");
    outfile << buffer;
    outfile.close();
    MusicFile tempMusicFile("temp.music");
    tempMusicFile.Play(timeInBetweenNotes);
    remove("temp.music");
}

KC::MusicFile::MusicFile(const std::string& filename): Buffer("")
{
    ParseMusicFile(filename);
}

KC::MusicFile::MusicFile(std::string&& filename): Buffer("")
{
    ParseMusicFile(filename);
}

void KC::MusicFile::ParseMusicFile(const std::string& fileName)
{
    std::ifstream infile(fileName);
    std::string line;
    std::stringstream buffer("");
    auto fileStart = false, fileEnd = false, musicStart = false;
    auto bpm = 0;
    auto baseNote = 0;
    while (std::getline(infile, line))
    {
        std::locale loc;
        for (auto& i : line)
        {
            i = std::toupper(i, loc);
        }
        const auto commentChar = line.find("//");
        if (commentChar != std::string::npos)
        {
            line[commentChar] = '\0';
            line = line.c_str(); // NOLINT(readability-redundant-string-cstr)
        }

        const auto sofChar = line.find("00");
        if (!fileStart && sofChar != std::string::npos)
        {
            fileStart = true;
            line[sofChar] = '\0';
            line = &line[sofChar + 2];
        }
        if (fileStart && bpm == 0)
        {
            const auto bpmMarker = line.find("BPM=");
            if (bpmMarker != std::string::npos)
            {
                bpm = std::stoi(&line[bpmMarker + 4]);
            }
        }
        if (fileStart && baseNote == '\0')
        {
            const auto bnMarker = line.find("BN=");
            if (bnMarker != std::string::npos)
            {
                baseNote = line[bnMarker + 3];
                line[bnMarker] = '\0';
                line = &line[bnMarker + 3];
            }
        }
        if (fileStart && !musicStart)
        {
            const auto musicStartMarker = line.find("M0");
            if (musicStartMarker != std::string::npos)
            {
                musicStart = true;
                line[musicStartMarker] = '\0';
                line = &line[musicStartMarker + 2];
            }
        }
        if (fileStart && musicStart && !fileEnd)
        {
            const auto eofChar = line.find("FF");

            if (eofChar != std::string::npos)
            {
                fileEnd = true;
                line[eofChar] = '\0';
                line = line.c_str(); // NOLINT(readability-redundant-string-cstr)
                break;
            }
            buffer << ' ' << line;
        }
    }

    TestFileParsing(fileStart, fileEnd, musicStart, bpm, baseNote);

    SetLocals(buffer, bpm, baseNote);

    infile.close();
}

auto KC::MusicFile::Play(const DWORD timeToWaitInBetweenNotes) const -> void
{
    auto noteTime = timeToWaitInBetweenNotes;
    std::stringstream playStream(Buffer);
    std::string note = "Initialized";
    size_t openLoopPosition = 0;
    size_t closeLoopPosition = 0;
    while (!playStream.eof() && note[0] != '\0')
    {
        auto durationOffset = 1.0;
        auto sleepOffset = 1.0;
        auto noteOffset = 0;
        playStream >> note;
        switch (note[0])
        {
        case '+':
            noteTime = static_cast<DWORD>(timeToWaitInBetweenNotes * 0);
            break;
        case '[':
            if (!openLoopPosition)
            {
                openLoopPosition = Buffer.find('[');
            }
            break;
        case ']':
            if (openLoopPosition)
            {
                closeLoopPosition = Buffer.find(']');
                playStream = std::stringstream(&Buffer[openLoopPosition + 1]);
                openLoopPosition = 0;
            }
            break;
        case '|':
            if (closeLoopPosition)
            {
                playStream = std::stringstream(&Buffer[closeLoopPosition + 1]);
                closeLoopPosition = 0;
            }
            break;
        default:
            for (auto i = 0; i < 3; i++)
            {
                switch (note[i])
                {
                case '_':
                    noteOffset = -1;
                    break;
                case '#':
                    noteOffset = 1;
                    break;
                case '.':
                    durationOffset = 1.5;
                    break;
                case 'T':
                    sleepOffset = 1.25;
                    break;
                default: ;
                }
            }
            const auto indexOffset = (noteOffset ? 1 : 0) + (durationOffset == 1.5 ? 1 : 0) + (
                sleepOffset == 1.25 ? 1 : 0);
            if (note[indexOffset] == '0')
            {
                Sleep(static_cast<DWORD>(durationOffset * *(&WholeNoteDuration + ConvertNoteToIndex(
                        static_cast<NoteLength>(note[indexOffset + 1]))) +
                    noteTime * sleepOffset));
            }
            else
            {
                PlayNote(FetchTone(std::stoi(&note[indexOffset + 1]), note[indexOffset], noteOffset),
                         static_cast<DWORD>(durationOffset * *(&WholeNoteDuration + ConvertNoteToIndex(
                             static_cast<NoteLength>(note[indexOffset + 2])))),
                         static_cast<DWORD>(noteTime * sleepOffset));
            }
            noteTime = timeToWaitInBetweenNotes;
            break;
        }
    }
}
