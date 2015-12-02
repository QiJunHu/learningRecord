#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>

class Folder
{
    public:
         void addMsg(Message* );
        void removeMsg(Message *);
    private:
        std::set<Message* > _messages;

};

void Folder::addMsg(Message * pMsg)
{
    _messages.insert(pMsg);
}


void Folder::removeMsg(Message * pMsg)
{
    _messages.erase(pMsg);
}

class Message
{
    public:
        //initailize object of Message ,  folders is initailized to the empty set
        Message(const std::string str = ""):contents(str) {}
        // copy constrol
        Message(const Message &);
        Message& operator= (const Message &);
        ~Message();
        void addFolder(Folder *);
        void removeFolder(Folder *);
        void _save(Folder &);
        void _remove(Folder &);
    private:
        std::string contents;
        std::set<Folder *> folders;
        void put_msg_in_Folders(const std::set<Foler *> &);
        void remove_msg_from_Folders();

};

Message::Message(const Message &m):contents(m.contents),folders(m.folders)
{
        put_msg_in_Folders(folders);
}

Message& Message::operator= (const Message &m)
{
        if(&m != this)
        {
            remove_msg_from_Folders();
            contents = m.contents;
            folders = m.folders
            put_msg_in_Folders(m.folders);
        }
    return *this;
}



 Message::~Message()
 {
     remove_msg_from_Folders();
 }


 void Message::addFolder(Folder * pFolder)
 {
     folders.insert(pFolder);

 }

 void Message::removeFolder(Folder * pFoler)
 {
     folders.erase(pFolder);
 }


 void Message::_save(Folder & rhs)
 {
     folders.insert(&ths);
     rhs.addMsg(this);
 }

void Message::_remove(Folder& rhs)
{
    folders.erase(&rhs);
    rhs.removeMsg(this);
}


void Message::put_msg_in_Folders(const std::set<Foler *> & rhs)
{

    for(std::set<Folder* >::const_iterator beg = folders.begin()  ;   beg != folders.end()  ;   ++ beg)
    {
        (*beg)->addMsg(this);
    }

}



void Message::remove_msg_from_Folders()contents
{
     for(std::set<Folder* >::const_iterator beg = folders.begin()  ;   beg != folders.end()  ;   ++ beg)
    {
        (*beg)->removeMsg(this);
     }
}



    return 0;
}