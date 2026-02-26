🎵 MP3 Tag Reader in C
🔎 Binary-Level ID3v2 Metadata Parser
🚀 Project Overview

This project is a command-line MP3 Tag Reader implemented in C that extracts metadata from MP3 files by manually parsing ID3v2 tags at the binary level.

Instead of using external libraries, the program reads and interprets raw byte streams directly from the MP3 file, following the official ID3v2 specification.

It demonstrates strong understanding of:

Binary file handling

Byte-level parsing

Frame-based data extraction

Endianness handling

Modular C programming

🎯 Objective

MP3 files store metadata such as:

Song Title

Artist

Album

Year

Genre

Comment

inside structured ID3v2 frames.

This project manually decodes those frames using low-level C file operations.

🔍 ID3v2 File Structure

An MP3 file containing ID3v2 metadata begins with:

3 bytes → "ID3" identifier

2 bytes → Version

1 byte → Flags

4 bytes → Tag Size

After the header, metadata frames follow.

🧩 Frame Format

Each ID3 frame contains:

4 bytes → Frame ID (TIT2, TPE1, etc.)

4 bytes → Frame Size

2 bytes → Flags

Frame Data

🎼 Supported Frames
Frame ID	Description
TIT2	Title
TPE1	Artist
TALB	Album
TYER	Year
TCON	Genre
COMM	Comment
⚙️ How the Program Works

Opens MP3 file in binary mode

Validates "ID3" signature

Reads header and calculates tag size

Iterates through frames

Extracts metadata using frame size

Prints formatted output in terminal

The implementation carefully handles:

Byte-order interpretation

Frame boundary validation

Safe memory handling

File pointer repositioning using fseek

🛠 Technologies Used

C Programming

GCC Compiler

Linux Terminal

fread(), fseek()

Structures

Defensive error handling

Modular program design
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
```
⚙️ Compilation

Compile using:

gcc *.c

This generates:

a.out

▶️ Execution

Run the program using:

./a.out sample.mp3

📌 Sample Output

MP3 Tag Reader

Title : Shape of You
Artist : Ed Sheeran
Album : Divide
Year : 2017
Genre : Pop
Comment: Sample Comment

🔎 Verification Using Hex Tools

To verify ID3 metadata manually:

xxd sample.mp3 | head

Expected output:

00000000: 4944 3303 0000 ...

49 44 33 corresponds to "ID3".

This confirms ID3v2 metadata presence.

🎯 Key Skills Demonstrated

Binary file parsing

Manual protocol decoding

Frame-based data interpretation

Memory-safe C programming

Systems-level debugging

📈 Learning Outcome

Through this project, I strengthened my understanding of:

File format internals

Metadata storage structure

Byte-level debugging

Clean modular C programming

This project aligns with my focus on Embedded Systems and low-level software development, where precise control over memory and data interpretation is critical.

👨‍💻 Author

Pavan
B.Tech Graduate
Focused on Embedded Systems & Core C Development
