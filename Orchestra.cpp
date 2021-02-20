#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Instrument{
public:
    virtual void makeSound()const = 0;
    virtual void play()const = 0;
private:
};

void Instrument::makeSound()const{
    cout << "To make a sound... ";
}

class BrassInstrument : public Instrument{
public:
    BrassInstrument(unsigned mouthpiece) : size(mouthpiece){}
    void makeSound()const{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }

private:
    unsigned size;
};

class Trumpet : public BrassInstrument{
public:
    Trumpet(unsigned mouthpiece) : BrassInstrument(mouthpiece){}
    void play()const{
        cout << "Toot ";
    }
private:
};

class Trombone : public BrassInstrument{
public:
    Trombone(unsigned mouthpiece) : BrassInstrument(mouthpiece){}
    void play()const{
        cout << "Blat ";
    }
private:
};

class StringInstrument : public Instrument{
public:
    StringInstrument(unsigned pitch) : pitch(pitch){}
    void makeSound()const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Violin : public StringInstrument{
public:
    Violin(unsigned pitch) : StringInstrument(pitch){}
    void play()const{
        cout << "Screech ";
    }
private:
};

class Cello : public StringInstrument{
public:
    Cello(unsigned pitch) : StringInstrument(pitch){}
    void play()const{
        cout << "Squawk ";
    }
private:
};

class PercussionInstrument : public Instrument{
public:
    PercussionInstrument(){}
    void makeSound()const{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};

class Drum : public PercussionInstrument{
public:
    Drum() : PercussionInstrument(){}
    void play()const{
        cout << "Boom ";
    }
private:
};

class Cymbal : public PercussionInstrument{
public:
    Cymbal() : PercussionInstrument(){}
    void play()const{
        cout << "Crash ";
    }
private:
};

class MILL{
public:
    MILL(){};
    void receiveInstr(Instrument& instrument){
        Instrument* iptr = &instrument;
        for(size_t i = 0; i < instruments.size(); i++){
            if(instruments[i] == nullptr){
                instruments[i] = iptr;
                return;
            }
        }
        instruments.push_back(iptr);
        return;
    }
    Instrument* loanOut(){
        for(size_t i = 0; i < instruments.size(); i++){
            if(instruments[i] != nullptr){
                Instrument* iptr = instruments[i];
                instruments[i] = nullptr;
                return iptr;
            }
        }
        return nullptr;
    }
    void dailyTestPlay()const{
        for(size_t i = 0; i < instruments.size(); i++){
            if(instruments[i] != nullptr){
                instruments[i] -> makeSound();
            }
        }
        return;
    }
private:
    vector<Instrument*> instruments;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

    void play()const{
        if(instr){
            instr -> play();
        }
        else{
            cout << "NOINSTR" << endl;
        }
    }

private:
    Instrument* instr;
};

class Orch{
public:
    void addPlayer(Musician& musician){
        if(musicians.size() == 25){
            cout << "Orchestra is too big!!" << endl;
            return;
        }
        Musician* mptr = &musician;
        musicians.push_back(mptr);
    }
    void play(){
        for(size_t i = 0; i < musicians.size(); i++){
            musicians[i] -> play();
        }
    }
private:
    vector<Musician*> musicians;
    int max = 25;
};



// PART ONE
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main
