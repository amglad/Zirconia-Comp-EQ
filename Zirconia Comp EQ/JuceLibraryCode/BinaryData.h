/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   compKnob_png;
    const int            compKnob_pngSize = 101637;

    extern const char*   eq_png;
    const int            eq_pngSize = 51062;

    extern const char*   footswitch_png;
    const int            footswitch_pngSize = 98767;

    extern const char*   fullLogo_png;
    const int            fullLogo_pngSize = 122774;

    extern const char*   knobLeft_png;
    const int            knobLeft_pngSize = 49980;

    extern const char*   knobRight_png;
    const int            knobRight_pngSize = 51123;

    extern const char*   light_png;
    const int            light_pngSize = 61730;

    extern const char*   logo_png;
    const int            logo_pngSize = 33284;

    extern const char*   off_png;
    const int            off_pngSize = 12560;

    extern const char*   on_png;
    const int            on_pngSize = 11122;

    extern const char*   switchLight_png;
    const int            switchLight_pngSize = 57529;

    extern const char*   volume_png;
    const int            volume_pngSize = 23008;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 12;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
