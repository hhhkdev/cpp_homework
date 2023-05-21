#include <iostream>
using namespace std;

#include "GraphicEditor.h"
#include "Shape.h"
#include "UI.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"

GraphicEditor::GraphicEditor() {
	pStart = NULL;
	pLast = NULL;
}

GraphicEditor::~GraphicEditor() { // �Ҹ���
	// ���� ������ ��� ��ü�� �����Ѵ�.
	Shape* p = pStart;
	while(p != NULL) {
		Shape* q = p->getNext(); // ���� ��ü��ġ�� �����Ѵ�.
		delete p; // ���� ��ü�� �����Ѵ�.
		p = q; // ���� ��ü�� ����Ų��.
	}
}

void GraphicEditor::paint() {
	// ���� ������ ��� ��ü�� �׸���.
	Shape* p = pStart;
	if(p == NULL) {
		UI::println("�׷��� ������ �����ϴ�.");
		return;
	}
	int i=0;
	// ó������ ������ ������ ���� �׷��� ������ �׸���.
	while(p != NULL) {
		UI::print(i); // �ε��� ���
		UI::print(": "); 
		p->paint(); // ���� �׸���
		p = p->getNext(); // ���� ������ ����Ų��.
		i++;
	}
}

void GraphicEditor::run() { // �׷��� �������� ���� �Լ�
	UI::println("�׷��� �������Դϴ�.");
	while(true) {
		int menu = UI::getMainMenu();
		switch(menu) {
			case EDIT: // ����
				edit(); break;
			case REMOVE: // ����
				remove(); break;
			case PAINT: // �ٽ� �׸���
				paint(); break;
			case EXIT: // ������
				return;
			default:
				UI::println("���� ���� ����");
		}
	}
}

void GraphicEditor::edit() {
	int shapeType = UI::getShapeType();
	switch(shapeType) {
		case LINE: // ����
			add(new Line()); break;
		case CIRCLE: // ��
			add(new Circle()); break;
		case RECT: // �簢��
			add(new Rect()); break;
		default:
			UI::println("���� ���� ����");
	}
}

void GraphicEditor::remove() {
	int shapeIndex = UI::getShapeIndex();
	remove(shapeIndex);
}

void GraphicEditor::remove(int shapeIndex) {
	// shapeIndex�� ���Ҹ� �����Ѵ�.
	if(pLast == NULL) {
		UI::println("�׷��� ������ �����ϴ�.");
		return;
	}
	int i=0;
	Shape* p = pStart;
	Shape* beforeP = pStart;
	while(i<shapeIndex) {
		i++;
		beforeP = p;
		p = p->getNext(); // ���� ��ü�� ����Ų��.
		if(p == NULL) { // shapeIndex�� ������ �������� ŭ
			UI::println("������ �ε����� �������� Ů�ϴ�.");
			return;
		}
	}

	// p�� ������ ������ ���� ������
	Shape* pNext = beforeP->add(p->getNext());
	delete p;
	if(p == pStart) // ������ ������ ù ������ ���
		pStart = pNext;

	if(p == pLast) { // ������ ������ ������ ������ ���
		if(pStart == NULL) // ������ ������ ó������ �������� ���
			pLast = NULL;
		else
			pLast = beforeP;	
	}
}

void GraphicEditor::add(Shape* p) {
	if(pStart == NULL) { // ó������ ���� ��ü�� �����Ͽ��� ��
		pStart = p;
		pLast = p;
		return;
	}
	else {
		pLast->add(p); // ���� p�� �������� �ܴ�.
		pLast = p; // pLast�� ������ �������� �����Ѵ�.
	}
}