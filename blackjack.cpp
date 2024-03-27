#include <iostream>

#include <stdbool.h>
#include<iomanip>
#include <stdio.h>
#include <vector>
#include<algorithm>
using namespace std;
class LcgGenerator{
private:
    uint16_t mA, mC, mCurrentX, mM;
public:
    LcgGenerator(uint16_t A,uint16_t C,uint16_t CurrentX,uint16_t M){
        mA=A;
        mC=C;
        mCurrentX=CurrentX;
        mM=M;
    }
    uint16_t next(){
        return mCurrentX =(mA*mCurrentX+mC)%mM;
    }
};
class Card{
private:
    string mSuite;
    uint16_t mValue;
public:
    Card(){
        mSuite="";
        mValue=0;
    }
    Card(string Suite, uint16_t Value){
        mSuite=Suite;
        mValue=Value;
    }
    bool operator == (const Card&altCard)const{
        if ((mSuite==altCard.mSuite && mValue==altCard.mValue))

            return true;
        else
            return false;
    }

    string toString() const{
        return to_string(mValue) +","+ mSuite;
    }
    bool isFake()const {

        if ((mSuite !="romb" && mSuite !="rosu" && mSuite !="trefla" && mSuite !="negru") || (mValue <2 || mValue>14))
            return true;
        return false;
    }
    uint16_t getBlackjackValue()const{
        int a;
        if(mValue<10)return mValue;
        else if(mValue >=10) return 10;
        return mValue;
    }

};

class CardPack: public Card{
private:
    vector <Card> mCards;
    uint16_t mCurrentIndex;
    string command;
public:
    CardPack(bool empty = true){
        if (empty == true){
            mCards.clear();
            mCurrentIndex=0;
        }
        else{
            mCards.resize(47);
            mCurrentIndex=0;
        }

    }
    bool goodForBackjack()const{

        int k=0;
        for(int i=0; i<mCards.size(); i++)
        {
            if(mCards[i].isFake()==false)
                k++;
            if(k==mCards.size())
                return true;
        }
        return false;
    }
    bool ok()const{
        if(mCards.size()!=52){
            return false;
        }
        for(int i=0; i<mCards.size();i++){
            for(int j=i+1; j<mCards.size();j++){
                if(mCards[i]==mCards[j]){
                    return false;
                }
            }}
        for(int i=0; i<mCards.size(); i++)
        {
            if(mCards[i].isFake()==true){
                return false;
            }
        }
        return true;
    }
    void addCard(const Card & altCard){
        mCards.push_back(altCard);
    }
    void shuffle(uint16_t a1, uint16_t c1, uint16_t x01, uint16_t a2, uint16_t c2, uint16_t x02){
        int m=0,n=0;
        mCurrentIndex=0;
        LcgGenerator Card1 (a1,c1,x01,mCards.size());
        LcgGenerator Card2 (a2,c2,x02,mCards.size());
        for(int j=0; j<50; j++){
            m=Card1.next();
            n=Card2.next();
            swap(mCards[m],mCards[n]);
        }
    }
    void printPack()const{
        for(int i=0; i<mCards.size(); i++){
            cout<< mCards[i].Card :: toString()<<endl;
        }
    }
    Card nextCard(){
        return mCards[mCurrentIndex++];
    }

};
class Player{
private:
    string mName;
    uint16_t mMoney, mPoints;
public:
    Player(){
        mName="Dealer";
        mMoney=0;
        mPoints=0;
    }
    Player(string Name, uint16_t Money){
        mName=Name;
        mMoney=Money;
        mPoints=0;
    }
    string toString()const{
        return mName + ":"+ to_string(mMoney);
    }
    void pick(const Card & altCard){
        mPoints=mPoints+altCard.getBlackjackValue();
    }
    void play(CardPack & altCardPack){
        while(mPoints<=16){
            mPoints+=altCardPack.nextCard().getBlackjackValue();
        }
    }
    void newRound(){
        mPoints=0;
    }
    bool lostRound()const{
        if(mPoints>21)
            return true;
        return false;
    }
    uint16_t getPoints()const{
        return mPoints;
    }
    string getName()const{
        return mName;
    }
    uint16_t getMoney()const{
        return mMoney;
    }
    void operator --() {
        mMoney=mMoney-10;
    }
    void operator ++(){
        mMoney=mMoney+10;
    }
    bool lostGame()const{
        if(mMoney<10){
            return true;
            return false;
        }
    }
};

int main() {
    string comanda;
    cin>>comanda;
    CardPack card;
    CardPack *CARD;
    vector <Card> carte;
    if(comanda=="check_cards"){
        string semn;
        uint16_t valoare,m=0;
        while(cin>>valoare){
            getchar();
            cin>>semn;
            card.addCard( Card(semn, valoare));
        }
        if(card.goodForBackjack()==true){
            if(card.ok()==true){
                cout<< "Pachet OK"<<endl;
            }
            else
                cout<<"Pregatit pentru Blackjack"<<endl;
        }
        else
            cout<<"Pachet masluit"<<endl;
    }
    else if(comanda=="shuffle_cards"){
        uint16_t A1,C1,X01, A2, C2, X02, valoare;
        string semn;
        CardPack pachet;
        cin>>A1>>C1>>X01>>A2>>C2>>X02;
        while(cin>>valoare){
            getchar();
            cin>>semn;
            pachet.addCard( Card(semn, valoare));

        }
        pachet.shuffle(A1,C1,X01,A2,C2,X02);
        pachet.printPack();
    }
    else if(comanda=="play_game") {
        int n;
        vector<Player> jucatori;
        string nume_jucator, semn;
        uint16_t bani, valoare;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> nume_jucator >> bani;
            jucatori.push_back(Player(nume_jucator, bani));
        }
        jucatori.push_back(Player("dealer", 500));
        uint16_t A1, C1, X01, A2, C2, X02;
        CardPack pachet;
        for (int i = 2; i < 11; i++) {
            pachet.addCard(Card("rosu", i));
        }
        for (int i = 12; i < 15; i++) {
            pachet.addCard(Card("rosu", 10));
        }
        for (int i = 2; i < 11; i++) {
            pachet.addCard(Card("negru", i));
        }
        for (int i = 12; i < 15; i++) {
            pachet.addCard(Card("negru", 10));
        }
        for (int i = 2; i < 11; i++) {
            pachet.addCard(Card("romb", i));
        }
        for (int i = 12; i < 15; i++) {
            pachet.addCard(Card("romb", 10));
        }
        for (int i = 2; i < 11; i++) {
            pachet.addCard(Card("trefla", i));
        }
        for (int i = 12; i < 15; i++) {
            pachet.addCard(Card("trefla", 10));
        }

        while (cin >> A1) {
            cin >> C1 >> X01 >> A2 >> C2 >> X02;
            pachet.shuffle(A1, C1, X01, A2, C2, X02);
            for (int i = 0; i < n + 1; i++) {
                jucatori[i].newRound();
                jucatori[i].pick(pachet.nextCard());
                jucatori[i].pick(pachet.nextCard());
            }
            for (int i = 0; i < n + 1; i++) {
                jucatori[i].play(pachet);
            }
            if (jucatori[n].getPoints() > 21) {
                for (int i = 0; i < n + 1; i++) {
                    if (jucatori[i].getPoints() <= 21) {
                        jucatori[i].operator++();
                    } else { jucatori[i].operator--();
                    }
                }}
            if (jucatori[n].getPoints() <= 21) {
                for (int i = 0; i < n+1; i++) {
                    if (jucatori[i].getPoints() > jucatori[n].getPoints() && jucatori[i].getPoints()<=21) {
                        jucatori[i].operator++();
                    } else if (jucatori[i].getPoints() < jucatori[n].getPoints() ||jucatori[i].getPoints()>21)
                    { (jucatori[i].operator--()); }
                }

            }
            for (int i = 0; i < n; i++) {
                if (jucatori[i].getMoney() < 10) {
                    vector<Player>::iterator it = jucatori.begin() + i;
                    jucatori.erase(it);
                    jucatori.resize(n-1);
                    n=n-1;

                }


            }
        }

        for (int i = 0; i < n; i++) {
            cout << jucatori[i].getName() << ": " << jucatori[i].getMoney() << endl;

        }



    }
    return 0;
}

