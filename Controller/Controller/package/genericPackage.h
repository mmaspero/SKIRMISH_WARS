#pragma once
class genericPackage
{
public:
	int getType() {return type;};
	char * getBuff() { return bufferData; };
	void setBuff(char * buff) { bufferData = buff; };
	void setSizeBuff(int size) { sizeBuff = size; };
	int getSizeBuff() { return sizeBuff; };
protected:
	int type;
	char * bufferData;
	int sizeBuff;
};