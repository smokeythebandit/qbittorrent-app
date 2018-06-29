#include "Categories.h"

Categories::Categories(QString name, QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent), m_name(name)
{

}
QString Categories::name() const {
	return m_name;
}

bool Categories::selected() const {
	return m_selected;
}

void Categories::setSelected(bool selected) {
	m_selected = selected;
	emit selectedChanged();
}

void Categories::remove() {
	post(urlWithPath("/command/removeCategories"), name());
}

