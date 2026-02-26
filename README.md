# id3-mp3-tag-reader-c
Binary-level MP3 metadata reader implemented in C by manually parsing ID3v2 frames without external libraries.

🚀 Project Overview

This project is a command-line MP3 Tag Reader implemented in C that extracts metadata from MP3 files by manually parsing ID3v2 tags at the binary level.

Unlike high-level libraries, this implementation works directly with raw byte streams, interpreting frame structures exactly as defined in the ID3 specification.

This project demonstrates strong control over:

Binary file processing

Byte-level parsing

Frame-based data extraction

Endianness handling

Structured modular programming

🧠 Why This Project Is Important

Modern media players automatically display metadata like:

Song Title

Artist

Album

Year

Genre

But internally, this information is stored inside structured ID3 frames.

This project manually decodes those frames without using any external libraries — purely using C and file handling.

This reflects a strong systems-level mindset, where data is interpreted exactly as it is stored in memory.

🔍 Understanding ID3v2 Structure

An MP3 file containing ID3v2 metadata begins with:

3 bytes → "ID3" identifier

2 bytes → Version

1 byte → Flags

4 bytes → Tag Size

After the header, multiple frames follow.

Each frame contains:

4 bytes → Frame ID (e.g., TIT2, TPE1)

4 bytes → Frame Size

2 bytes → Flags

Frame Data

🎼 Supported Frame IDs
Frame ID	Meaning
TIT2	Title
TPE1	Artist
TALB	Album
TYER	Year
TCON	Genre
COMM	Comment
⚙️ Internal Working

The program:

Opens MP3 file in binary mode

Validates "ID3" signature

Reads header and calculates tag size

Iterates frame-by-frame

Extracts frame data based on frame size

Converts binary data into readable text

Displays metadata cleanly in terminal

The implementation carefully handles:

Byte-order interpretation

Frame boundary validation

Safe memory handling

File pointer repositioning using fseek

🛠 Technologies Used

C Programming

GCC Compiler

Linux Terminal

Binary File Handling (fread, fseek)

Structures

Byte-level parsing logic

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
🔎 Verifying ID3 Tag Using Hex Tools

To inspect the MP3 file header:

xxd sample.mp3 | head

You should see:

00000000: 4944 3303 0000 ...

49 44 33 corresponds to "ID3".

This confirms the presence of ID3v2 metadata.

🎯 Core Concepts Strengthened

Binary file parsing

Manual protocol decoding

Frame-based data structures

Endianness awareness

Defensive coding practices

Modular C design

📈 Learning Outcome

Through this project, I developed a deeper understanding of:

How structured data is stored inside files

How metadata is organized at the byte level

How to interpret file format specifications

How to debug using hex inspection tools

This project reflects my growing focus on Embedded Systems and low-level programming, where precise control over memory and data interpretation is critical.

👨‍💻 Author

Pavan
B.Tech Graduate
Focused on Embedded Systems & Core C Development
