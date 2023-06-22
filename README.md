# Binary-encoded JSON parser
# The task
Write a Binary-encoded JSON (BEJ) parser.

At its core, BEJ is a self-describing binary format for hierarchical data that is designed to
be straightforward for both encoding and decoding. Unlike in ASN.1, BEJ uses no contextual encodings; everything is explicit and direct. While this requires the insertion of a bit more metadata into BEJ-encoded data, the tradeoff benefit is that no lookahead is required in the decoding process. The result is a significantly streamlined representation that fits in a very small memory footprint suitable for modern embedded processors.

Your task is to write a program that would convert BEJ to JSON.

For more information refer to DSP0218 specification, section 7.

A reference implementation in Python is here. The pldm_bej_encoder_decoder.py file implements the functionality


# Requirements
● Language: pure C without any C++ features.

● Compiler: either GCC or Clang (no MSVS C compiler)

● Don’t link against 3d party libraries except for libc.

● Interface: pass dictionary and BEJ files as input and save JSON as UTF-8 text file.

● Write CMakefiles for your project

● The code should conform to one of the coding styles. For example: https://www.gnu.org/prep/standards/standards.html#Formatting

● Write unit tests for your project with a popular UnitTest framework like GoogleTest or any other. It is time-consuming so you may cover only selected complex functions

● Publish the code on Git repository on Github/Gitlab/Bitbucket

● Add Doxygen annotations to your project and generate documentation with the Doxygen. Don’t spend too much time on that.

● Minimize heap usage — that will improve memory safety.

● Create example data to demonstrate how your program works. Something not trivial.


# Example data
● DSP0218, section 7.6.1 contains an example of BEJ dictionary coding

● DSP0218, section 7.6.3 contains an example describing how to decode BEJ

● DSP8010 contains examples of BEJ-dictionaries (“dictionaries” directory of the zip archive)

● Real-world JSON data that maybe encoded as BEJ: https://redfish.dmtf.org/redfish/mockups/v1/1354

