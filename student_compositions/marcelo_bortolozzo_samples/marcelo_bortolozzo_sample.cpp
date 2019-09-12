#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include "../../read_write_wav.h"
using namespace std;



float midi2freq(int m)
{
    return 440*pow(2,(m-69.0f)/12.0f);
}

float freq2midi(float freq)
{
    return 12*log2( freq/440) + 69;
}



class SoundProcessor  
{
    public:

        virtual void process(float*, int)
        {
        }
};


class SamplerPlayback : public SoundProcessor
{
    public: 

        float amp;
        int Fs;
        float* wav_buffer;
        int n_channels;
        int wav_len;

        SamplerPlayback(float _amp, string wavFileName)
        {
            amp = _amp;
            cout << "reading wav file..." << endl;
            float* buffer;
            n_channels = read_wave_file(wavFileName.c_str(), buffer, &wav_len, &Fs);
            wav_buffer = (float*) malloc(wav_len/n_channels*sizeof(float));
            // copy left channel to internal buffer
            for (int i=0; i<wav_len; i+=n_channels)
            {
                 wav_buffer[i/n_channels] = buffer[i]; 
            }
            // update the length since we are using only left channel
            wav_len = wav_len/n_channels;
            delete [] buffer;
        }

        ~SamplerPlayback()
        {
        }   

        void process(float* audio_buffer, int buffer_len) 
        {
            float c=0;
            int ramp_size = 500;
            cout << "sampler class -> call process: "<<  buffer_len << " amp: "<<  amp << "  Fs: " << Fs << endl;
            for (int n=0; n<buffer_len; n++)
            {
               //TODO hop size for adjust pitch
                float wavSample = wav_buffer[ n % wav_len];
                audio_buffer[n] += (c/ramp_size)*amp * wavSample; 
                // fadein/fadeout
                if (n<ramp_size-1) c++; 
                if (n>=buffer_len-ramp_size) c--;
            }
        }

};

class MusicNote
{
    public:
        float start_time; // pos in seconds
        float end_time; // pos in seconds
        SoundProcessor* sampler;   

    MusicNote(SoundProcessor *o, float s, float e):sampler(o), start_time(s), end_time(e)
    {
    }
};



int main(int c, char** argv)
{
    const float duration = 3.5; //seconds
    const float Fs = 44100; //sample rate (samples /second)
    const int buffer_len = round(duration*Fs); // samples
    float *audio_buffer;
    vector<MusicNote> notes;

    // ==========================================================
    // MAKE YOUR MUSIC HERE!!!!!
    //===============================
    SamplerPlayback* s1 = new SamplerPlayback(0.7, "./student_compositions/marcelo_bortolozzo_samples/intro_sample.wav");
    MusicNote m1(s1, 0, 4.3);
    notes.push_back(m1);

    SamplerPlayback* s2 = new SamplerPlayback(0.7, "./student_compositions/marcelo_bortolozzo_samples/intro_rep.wav");


    MusicNote m12(s2, 4.25, 7.9);
    notes.push_back(m12);

    SamplerPlayback* s3 = new SamplerPlayback(0.8, "./student_compositions/marcelo_bortolozzo_samples/passar_sample.wav");
    MusicNote m2(s3, 7.8, 9);
    notes.push_back(m2);

    SamplerPlayback* s4 = new SamplerPlayback(0.6, "./student_compositions/marcelo_bortolozzo_samples/chords_sample.wav");
    MusicNote m3(s4, 8.8, 15);
    notes.push_back(m3);

    MusicNote m4(s3, 15, 15.3);
    notes.push_back(m4);

    MusicNote m5(s3, 15.2, 15.4);
    notes.push_back(m5);

    MusicNote m6(s3, 15.3, 15.5);
    notes.push_back(m6);

    MusicNote m7(s3, 15.6, 16.7);
    notes.push_back(m7);

    SamplerPlayback* s6 = new SamplerPlayback(0.8, "./student_compositions/marcelo_bortolozzo_samples/drum.wav");
    MusicNote m71(s6, 16.6, 20);
    notes.push_back(m71);

    SamplerPlayback* s5 = new SamplerPlayback(1.2, "./student_compositions/marcelo_bortolozzo_samples/bass.wav");
    MusicNote m8(s5, 15.8, 16.6);
    notes.push_back(m8);

    SamplerPlayback* s7 = new SamplerPlayback(0.8, "./student_compositions/marcelo_bortolozzo_samples/bass.wav");
    MusicNote m9(s7, 16.6, 17);
    notes.push_back(m9);

    MusicNote m10(s7, 17, 17.4);
    notes.push_back(m10);

    MusicNote m11(s7, 17.4, 18.2);
    notes.push_back(m11);

    MusicNote m13(s7, 18.2, 19);
    notes.push_back(m13);

    MusicNote m14(s7, 19, 19.4);
    notes.push_back(m14);

    MusicNote m15(s7, 19.4, 19.8);
    notes.push_back(m15);

    MusicNote m16(s3, 19.8, 21.1);
    notes.push_back(m16);

    // ==========================================================

    //===============================
    // get max signal duration
    int maxPos = 0;
    for (int k=0; k<notes.size(); k++)
    {
        maxPos = std::max((float)maxPos, (float)round(notes[k].end_time*Fs));
    }
    audio_buffer = new float[maxPos];
    memset(audio_buffer, 0, maxPos);

    cout << "maxPos: " << maxPos <<  endl;
    // write the notes into the audio buffer
    for (int k=0; k<notes.size(); k++)
    {
        int startPos = notes[k].start_time*Fs;
        int endPos = notes[k].end_time*Fs;
        cout << "startPos: " << startPos << endl;
        cout << "endPos: " << endPos << endl;
        cout << "opa" << endl;
        notes[k].sampler->process(audio_buffer + startPos, endPos-startPos);
    }

    // ============================
    // save output wave
    string wav_name = "sampler.wav";
    write_wave_file (wav_name.c_str(), audio_buffer, maxPos, Fs);
    cout << "done." << endl;
    delete [] audio_buffer;
    return 0;
}



