*🎵 #MP3 Tag Reader in C*
🔎 Binary-Level ID3v2 Metadata Parser
🚀 Project Overview

This project is a command-line MP3 Tag Reader implemented in C that extracts metadata from MP3 files by manually parsing ID3v2 tags at the binary level.

Instead of using external libraries, this program reads and interprets raw byte streams directly from the MP3 file, following the official ID3v2 frame structure.

This demonstrates strong knowledge of:

Binary file handling

Byte-level parsing

Frame-based data extraction

Endianness awareness

Modular C programming

*🎯 Objective*

MP3 files store metadata such as:

Song Title

Artist

Album

Year

Genre

Comment

inside structured ID3 frames.

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

##🎼 Supported Frames
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

Prints formatted output to terminal

🛠 Technologies & Concepts Used

C Programming

GCC Compiler

Linux Terminal

fread(), fseek()

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
🔎 Verifying Using Hex Tool

To inspect the MP3 file header:

xxd sample.mp3 | head

Expected output:

00000000: 4944 3303 0000 ...

49 44 33 corresponds to "ID3".

This confirms ID3v2 metadata presence.

🎯 Key Skills Demonstrated

Binary file parsing

Manual protocol decoding

Memory-safe C programming

Frame-based data interpretation

Systems-level debugging using hex tools

📈 Learning Outcome

Through this project, I developed deeper understanding of:

File format internals

Metadata storage structure

Byte-level debugging

Writing clean and modular C programs

This project aligns with my focus on Embedded Systems and low-level software development.

👨‍💻 Author

Pavan
B.Tech Graduate
Focused on Embedded Systems & Core C Development
