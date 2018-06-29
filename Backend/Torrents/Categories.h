#ifndef CATEGORIES_H
#define CATEGORIES_H

//Qt framework
#include <QObject>

//Internal headers
#include "../AbstractApiInterface.h"

class Categories : public AbstractApiInterface
{
		Q_OBJECT
	public:
		Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
		Q_PROPERTY(QString name READ name)
		Categories(QString name, QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

		/**
		 * @brief name Gets the name of this category
		 * @return the name of the category
		 */
		QString name() const;

		/**
		 * @brief selected Gets if torrents in this category should be shown
		 * @return returns true if selected
		 */
		bool selected() const;

		/**
		 * @brief setSelected Sets if torrents in this category should be shown
		 * @param selected if this category should be selected
		 */
		void setSelected(bool selected);

		/**
		 * @brief remove Removes this torrent
		 */
		void remove();


	signals:
		/**
		 * @brief selectedChanged is emitted when selected has changed
		 */
		void selectedChanged();

	private:
		bool m_selected;
		QString m_name;
};

#endif // CATEGORIES_H
