#include "Categorie.h"

Categorie::Categorie(QString name, QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent), m_selected(false), m_name(name)
{

}
QString Categorie::name() const {
	return m_name;
}

bool Categorie::selected() const {
	return m_selected;
}

void Categorie::setSelected(bool selected) {
	m_selected = selected;
	emit selectedChanged();
}

void Categorie::remove() {
    post(urlWithPath("/command/removeCategories"), name().toLatin1());
}

void Categorie::update()
{

}

