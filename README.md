🎵 MP3 Tag Reader in C
🔎 Binary-Level ID3v2 Metadata Parser
🚀 Project Summary

This is a command-line MP3 Tag Reader implemented in C that extracts metadata from MP3 files by manually parsing ID3v2 tags at the binary level.

The project reads raw byte streams and decodes structured frame data without using any external libraries.

It demonstrates strong understanding of:

Binary file processing

Byte-level parsing

Frame-based data structures

Endianness handling

Modular C design

🎯 Problem Statement

MP3 files store metadata such as:

Title

Artist

Album

Year

Genre

inside structured ID3v2 frames.

Most applications use libraries to read this data.

This project manually decodes those frames directly from the binary file structure.

🔍 ID3v2 File Structure Overview

An MP3 file with ID3v2 metadata begins with:

3 bytes → "ID3" identifier

2 bytes → Version

1 byte → Flags

4 bytes → Tag Size

After the header, multiple metadata frames follow.

🧩 Frame Structure

Each metadata frame contains:

4 bytes → Frame ID (TIT2, TPE1, etc.)

4 bytes → Frame Size

2 bytes → Flags

Frame Data

🎼 Supported Frames
Frame ID	Meaning
TIT2	Title
TPE1	Artist
TALB	Album
TYER	Year
TCON	Genre
COMM	Comment
⚙️ How the Program Works

Opens MP3 file in binary mode

Validates "ID3" signature

Reads and interprets header

Calculates total tag size

Iterates through frames

Extracts metadata based on frame size

Displays formatted output in terminal

🛠 Technologies & Concepts Used

C Programming

GCC Compiler

Linux Terminal

fread, fseek

Structures

Byte-order interpretation

Defensive error handling

Modular design
```

📂 Project Structure
mp3-tag-reader/
│
├── main.c
├── read_tag.c
├── read_tag.h
├── types.h
├── sample.mp3
└── README.md
⚙️ Compilation

```
gcc *.c

This generates:

a.out
▶️ Execution
./a.out sample.mp3
📌 Sample Output
MP3 Tag Reader

Title  : Shape of You
Artist : Ed Sheeran
Album  : Divide
Year   : 2017
Genre  : Pop
Comment: Sample Comment
🔎 Binary Verification (Using Hex Tools)

To verify ID3 tag manually:

xxd sample.mp3 | head

Expected:

00000000: 4944 3303 0000 ...

49 44 33 → "ID3"

This confirms ID3v2 metadata presence.

💡 Key Learning Outcomes

Through this project, I strengthened:

Binary-level debugging skills

File format interpretation

Manual protocol decoding

Memory-safe programming

Systems-level thinking

👨‍💻 Author

Pavan
B.Tech Graduate
Focused on Embedded Systems & Low-Level C Development
