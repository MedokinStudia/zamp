#include "klient.hh"


using namespace std;



int Send(int Sk2Server,
  const char * sMesg) {
  ssize_t IlWyslanych;
  ssize_t IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "!!! Blad przeslania napisu." << endl;
  }
  return 0;
}

void Fun_CommunicationThread(Sender * pSender) {
  pSender -> Watching_and_Sending();
}

Sender::Sender(int Socket, Scene * pScn): _Socket(Socket), _pScn(pScn) {
  this -> klient_thread = std::thread(Fun_CommunicationThread, this);
}

bool OpenConnection(int & rSocket) {
  struct sockaddr_in DaneAdSerw;

  bzero((char * ) & DaneAdSerw, sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);

  rSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (rSocket < 0) {
    cerr << "!!! Blad otwarcia gniazda." << endl;
    return false;
  }

  if (connect(rSocket, (struct sockaddr * ) & DaneAdSerw, sizeof(DaneAdSerw)) < 0) {
    cerr << "!!! Brak mozliwosci polaczenia do portu: " << PORT << endl;
    return false;
  }
  return true;
}

  void close(int Socket, Sender & ClientSender, thread t) {
  cout << "Close(połączenie zamknięte)\n" << endl;
  Send(Socket, "Close\n");
  ClientSender.CancelCountinueLooping();
  t.join();
  close(Socket);
}
