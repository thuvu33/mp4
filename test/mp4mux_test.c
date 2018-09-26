/** ASP 24.04.2010 @file
*  
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "mp4mux.h"

const unsigned char avc[] = {0, 0, 1, 0xB3, 0, 0x10, 7, 0, 0, 1, 0xB6, 16, 0x60, 0x51, 0x82, 0x3D, 0xB7, 0xEF};
const unsigned char sps[] = {0x67, 0x42, 0xE0, 0x0A, 0xDA, 0x79};
const unsigned char pps[] = {0x68, 0xCE, 0x04, 0x72};
const unsigned char idr[] = {0,0,0,12,0x65, 0xB8, 0x23, 0xFF, 0xFF, 0xF0, 0xF4, 0x50, 0x00, 0x10, 0x11, 0xF8};
const unsigned char frm[] = {0,0,0,4,0x61, 0xE2, 0x3D, 0x40 };

const unsigned char aac_dsi[] = {0x12, 0x10};
const unsigned char aac[] = {
0x21, 0x10, 0x05, 0x20, 0xA4, 0x1B, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x37, 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x70
};

void test(FILE * output)
{
    int i, id_video, id_audio, id_private;
    static unsigned char dummy[100];
    // == Open file
    MP4E_mux_t * mp4 = MP4E__open(output);

    // == Add audio track
    MP4E_track_t track;
    track.object_type_indication = MP4_OBJECT_TYPE_AUDIO_ISO_IEC_14496_3;
    strcpy((char*)track.language, "und");
    track.u.a.channelcount = 2;
    track.time_scale = 44100;
    track.default_duration = 1024;
    track.track_media_kind = e_audio;
    id_audio = MP4E__add_track(mp4, &track);
    
    // == Add video track
    track.track_media_kind = e_video;
    track.object_type_indication = MP4_OBJECT_TYPE_AVC;
    track.time_scale = 90000;
    track.default_duration = 90000 / 30;
    track.u.v.width = 16;
    track.u.v.height = 16;
    id_video = MP4E__add_track(mp4, &track);

    // == Add private data track
    track.track_media_kind = e_private;
    track.time_scale = 44100;
    track.default_duration = 1024;
    track.object_type_indication = MP4_OBJECT_TYPE_USER_PRIVATE;
    id_private = MP4E__add_track(mp4, &track);


    // == Supply SPS/PPS/DSI descriptors
    MP4E__set_sps(mp4, id_video, sps, sizeof(sps));
    MP4E__set_pps(mp4, id_video, pps, sizeof(pps));
    MP4E__set_dsi(mp4, id_audio, aac_dsi, sizeof(aac_dsi));
    for (i = 0; i < 10; i++)
    {
        dummy[i] = 16+i;
    }
    MP4E__set_dsi(mp4, id_private, dummy, 10);


    // == Append audio data
    for (i = 0; i < 2 * 44100 / 1024; i++)
    {
        MP4E__put_sample(mp4, id_audio, aac, sizeof(aac), 0, MP4E_SAMPLE_RANDOM_ACCESS);
    }
    // == Append video data
    for (i = 0; i < 30; i++)
    {
        MP4E__put_sample(mp4, id_video, idr, sizeof(idr), 0, MP4E_SAMPLE_RANDOM_ACCESS);
        MP4E__put_sample(mp4, id_video, frm, sizeof(frm), 0, MP4E_SAMPLE_DEFAULT);
    }
    // == Append private data
    for (i = 0; i < 2 * 44100 / 1024; i++)
    {
        int bytes = 100;
        int duration = 1024;
        dummy[0] = i;
        MP4E__put_sample(mp4, id_private, dummy, bytes, duration, MP4E_SAMPLE_DEFAULT);
    }

    // == Set file comment
    MP4E__set_text_comment(mp4, "test comment");
    
    // == Close session
    MP4E__close(mp4);
}

int main(int argc, char* argv[])
{
    FILE * file;
    char * input_file_name = (argc > 1)?argv[1]:"mp4mux_test.mp4";
    if (!input_file_name)
    {
        printf("ERROR: no file name given!\n");
        return 1;
    }
    file = fopen(input_file_name, "wb");
    if (!file)
    {
        printf("ERROR: can't open file %s!\n", input_file_name);
        return 1;
    }
    test(file);

    return 0;
}
