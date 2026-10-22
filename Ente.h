#pragma once
class Ente {
protected:
	int id;
public:
	Ente() {

	}
	virtual ~Ente() {

	}
	virtual void executar() = 0;
	void desenhar();
 };