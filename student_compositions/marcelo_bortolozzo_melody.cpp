#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include "../read_write_wav.h"
using namespace std;


float midi2freq(int m)
{
    return 440*pow(2,(m-69.0f)/12.0f);
}

float freq2midi(float freq)
{
    return 12*log2( freq/440) + 69;
}



class Oscillator   
{
    public:

        virtual void process(float*, int)
        {
        }
};


class SineOscillator : public Oscillator
{
    public: 

        float freq;
        float amp;
        float Fs;


        SineOscillator(int nota_midi, float _amp, float _Fs)
        {
            freq = midi2freq(nota_midi);
            amp = _amp;
            Fs = _Fs;
        }

        ~SineOscillator()
        {
        }   

        void process(float* audio_buffer, int buffer_len) 
        {
            float c=0;
            int ramp_size = 1000;
            cout << "sine class -> call process: "<<  buffer_len << " amp: "<<  amp << " freq: "<< freq << "  Fs: " << Fs << endl;
            for (int n=0; n<buffer_len; n++)
            {

                audio_buffer[n] += (c/ramp_size)*amp * sin(2*M_PI*freq*(((float)n)/Fs)); 
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
        Oscillator* osc;   

    MusicNote(Oscillator *o, float s, float e):osc(o), start_time(s), end_time(e)
    {
    }

    MusicNote(int note, float amp, float sample_rate, float s, float e) 
    : osc(new SineOscillator(note, amp, sample_rate)),
        start_time(s), end_time(e)
    {        
    }
};

inline float get_whole_note(int tempo)
{
    return 4*60.0/tempo;
}

inline float get_eighth_note(int tempo)
{
    return (60.0/tempo)/2;
}


int play_intro(int start_measure, vector<MusicNote*>* notes, int tempo, int Fs)
{
    int measure = start_measure;
    float whole_note = get_whole_note(tempo);
    float eighth_note = get_eighth_note(tempo);

    for(measure = start_measure; measure < start_measure + 1; measure++)
    {
        notes->push_back(new MusicNote(43, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(47, 0.5, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(55, 0.5, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(47, 0.5, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 2; measure++)
    {
        notes->push_back(new MusicNote(42, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(47, 0.5, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(54, 0.5, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(47, 0.5, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 3; measure++)
    {
        notes->push_back(new MusicNote(45, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(52, 0.5, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(48, 0.5, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(52, 0.5, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(55, 0.5, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(52, 0.5, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(48, 0.5, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(52, 0.5, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 4; measure++)
    {
        notes->push_back(new MusicNote(45, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(54, 0.5, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(54, 0.5, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(62, 0.5, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(54, 0.5, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(50, 0.5, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(54, 0.5, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }
    return measure;
}

int play_alt(int start_measure, vector<MusicNote*>* notes, int tempo, int Fs)
{
    int measure = start_measure;
    float whole_note = get_whole_note(tempo);
    float eighth_note = get_eighth_note(tempo);

    for(measure = start_measure; measure < start_measure + 1; measure++)
    {
        notes->push_back(new MusicNote(43, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(47, 0.3, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(55, 0.3, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(47, 0.3, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 2; measure++)
    {
        notes->push_back(new MusicNote(45, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(57, 0.3, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 3; measure++)
    {
        notes->push_back(new MusicNote(47, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(55, 0.3, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(52, 0.3, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(55, 0.3, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(59, 0.3, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(55, 0.3, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(52, 0.3, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(55, 0.3, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    for(; measure < start_measure + 4; measure++)
    {
        notes->push_back(new MusicNote(45, 0.4, Fs, (whole_note*measure), (whole_note*measure) + eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + eighth_note, (whole_note*measure) + 2*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 2*eighth_note, (whole_note*measure) + 3*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 3*eighth_note, (whole_note*measure) + 4*eighth_note));
        notes->push_back(new MusicNote(62, 0.3, Fs, (whole_note*measure) + 4*eighth_note, (whole_note*measure) + 5*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 5*eighth_note, (whole_note*measure) + 6*eighth_note));
        notes->push_back(new MusicNote(50, 0.3, Fs, (whole_note*measure) + 6*eighth_note, (whole_note*measure) + 7*eighth_note));
        notes->push_back(new MusicNote(54, 0.3, Fs, (whole_note*measure) + 7*eighth_note, (whole_note*measure) + 8*eighth_note));
    }

    notes->push_back(new MusicNote(43, 0.2, Fs, (whole_note*measure), (whole_note*measure) + whole_note));
    notes->push_back(new MusicNote(47, 0.2, Fs, (whole_note*measure), (whole_note*measure) + whole_note));
    notes->push_back(new MusicNote(50, 0.2, Fs, (whole_note*measure), (whole_note*measure) + whole_note));

    return measure + 1;
}

int play_melody(int start_measure, vector<MusicNote*>* notes, int tempo, int Fs)
{
    int measure = start_measure;
    float whole_note = get_whole_note(tempo);
    float eighth_note = get_eighth_note(tempo);
    float quarter_note = eighth_note*2;
    float half_note = quarter_note*2;
    float current_time = measure*whole_note;

    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(66, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(69, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(72, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(74, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(72, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(72, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(69, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(72, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(69, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;

    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(69, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(74, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(72, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(67, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(71, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;
    notes->push_back(new MusicNote(69, 0.5, Fs, current_time, current_time + eighth_note));
    current_time += eighth_note;    
    notes->push_back(new MusicNote(66, 0.5, Fs, current_time, current_time + half_note));
    current_time += half_note;
    notes->push_back(new MusicNote(62, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(66, 0.5, Fs, current_time, current_time + quarter_note));
    current_time += quarter_note;
    notes->push_back(new MusicNote(67, 0.2, Fs, current_time, current_time + whole_note));
    current_time += whole_note;

}   

int main(int c, char** argv)
{
    const float Fs = 44100; //sample rate (samples /second)
    float *audio_buffer;
    vector<MusicNote*> notes;

    int measure = 0;
    float tempo=80;
    float quarter_note = 60/tempo;
    float whole_note = quarter_note*4;
    float eighth_note = quarter_note/2;
    // ==========================================================
    // MAKE YOUR MUSIC HERE!!!!!

    // tempo count
    for(int i = 0; i < 4; i++)
    {
        Oscillator *s1 = new SineOscillator(80, 0.5, Fs);
        notes.push_back(new MusicNote(s1, i*quarter_note, i*quarter_note + 0.05));
    }
    measure++;
    measure = play_intro(measure, &notes, tempo, Fs);
    measure = play_alt(measure, &notes, tempo, Fs);
    play_melody(1, &notes, tempo, Fs);

    // ==========================================================

    //===============================
    // get max signal duration
    int maxPos = 0;
    for (int k=0; k<notes.size(); k++)
    {
        maxPos = std::max((float)maxPos, (float)round(notes[k]->end_time*Fs));
    }
    audio_buffer = new float[maxPos];
    memset(audio_buffer, 0, maxPos);

    cout << "maxPos: " << maxPos <<  endl;
    // write the notes into the audio buffer
    for (int k=0; k<notes.size(); k++)
    {
        int startPos = notes[k]->start_time*Fs;
        int endPos = notes[k]->end_time*Fs;
        cout << "startPos: " << startPos << endl;
        cout << "endPos: " << endPos << endl;
        cout << "opa" << endl;
        notes[k]->osc->process(audio_buffer + startPos, endPos-startPos);
    }

    // ============================
    // save output wave
    string wav_name = "melody_rand.wav";
    write_wave_file (wav_name.c_str(), audio_buffer, maxPos, Fs);
    cout << "done." << endl;
    delete [] audio_buffer;
    return 0;
}



