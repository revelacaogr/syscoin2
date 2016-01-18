/*
 * Syscoin Developers 2015
 */
#include "offerview.h"
#include "syscoingui.h"


#include "clientmodel.h"
#include "walletmodel.h"
#include "optionsmodel.h"
#include "myofferlistpage.h"
#include "myacceptedofferlistpage.h"
#include "acceptedofferlistpage.h"
#include "acceptandpayofferlistpage.h"
#include "offerlistpage.h"
#include "offertablemodel.h"
#include "offeraccepttablemodel.h"
#include "ui_interface.h"

#include <QAction>
#if QT_VERSION < 0x050000
#include <QDesktopServices>
#else
#include <QStandardPaths>
#endif
#include <QPushButton>

OfferView::OfferView(QStackedWidget *parent):
    clientModel(0),
    walletModel(0)
{

	tabWidget = new QTabWidget();
    offerListPage = new OfferListPage(this);
    myOfferListPage = new MyOfferListPage();
	acceptandPayOfferListPage = new AcceptandPayOfferListPage();
	myAcceptedOfferListPage = new MyAcceptedOfferListPage();
	acceptedOfferListPage = new AcceptedOfferListPage();

	tabWidget->addTab(myOfferListPage, tr("&Selling"));
	tabWidget->addTab(myAcceptedOfferListPage, tr("S&old"));
	tabWidget->addTab(acceptedOfferListPage, tr("&My Purchases"));
	tabWidget->addTab(offerListPage, tr("Search"));
	tabWidget->addTab(acceptandPayOfferListPage, tr("&Buy"));
	tabWidget->setTabIcon(0, QIcon(":/icons/cart"));
	tabWidget->setTabIcon(1, QIcon(":/icons/cart"));
	tabWidget->setTabIcon(2, QIcon(":/icons/cart"));
	tabWidget->setTabIcon(3, QIcon(":/icons/search"));
	tabWidget->setTabIcon(4, QIcon(":/icons/send"));
	parent->addWidget(tabWidget);
}

OfferView::~OfferView()
{

}

void OfferView::setSyscoinGUI(SyscoinGUI *gui)
{
    this->gui = gui;
}
void OfferView::setClientModel(ClientModel *clientModel)
{
    this->clientModel = clientModel;
    if (clientModel)
    {
       
        offerListPage->setOptionsModel(clientModel->getOptionsModel());
		myOfferListPage->setOptionsModel(clientModel,clientModel->getOptionsModel());
		myAcceptedOfferListPage->setOptionsModel(clientModel,clientModel->getOptionsModel());
		acceptedOfferListPage->setOptionsModel(clientModel,clientModel->getOptionsModel());
    }
}

void OfferView::setWalletModel(WalletModel *walletModel)
{

    this->walletModel = walletModel;
    if (walletModel)
    {

        offerListPage->setModel(walletModel, walletModel->getOfferTableModelAll());
		myOfferListPage->setModel(walletModel, walletModel->getOfferTableModelMine());
		myAcceptedOfferListPage->setModel(walletModel, walletModel->getOfferTableModelMyAccept());
		acceptedOfferListPage->setModel(walletModel, walletModel->getOfferTableModelAccept());

    }
}


void OfferView::gotoOfferListPage()
{
	tabWidget->setCurrentWidget(offerListPage);
}


bool OfferView::handlePaymentRequest(const SendCoinsRecipient* recipient)
{
    if (acceptandPayOfferListPage->handlePaymentRequest(recipient))
    {
        tabWidget->setCurrentWidget(acceptandPayOfferListPage);
        Q_EMIT showNormalIfMinimized();
        return true;
    }
    return false;
}
