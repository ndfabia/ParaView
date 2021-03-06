/*
* Copyright (c) 2007, Sandia Corporation
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the Sandia Corporation nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Sandia Corporation ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Sandia Corporation BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ClientTableDisplay.h"
#include "ui_ClientTableDisplay.h"

#include <pqApplicationCore.h>
#include <pqComboBoxDomain.h>
#include <pqNamedWidgets.h>
#include <pqOutputPort.h>
#include <pqPipelineSource.h>
#include <pqPropertyHelper.h>
#include <pqPropertyLinks.h>
#include <pqPropertyManager.h>
#include <pqServerManagerModel.h>
#include <pqSignalAdaptors.h>
#include <pqSignalAdaptorSelectionTreeWidget.h>

#include <vtkDataSetAttributes.h>
#include <vtkGraph.h>
#include <vtkSMClientDeliveryRepresentationProxy.h>
#include <vtkSMProperty.h>
#include <vtkSMPropertyHelper.h>
#include <vtkSMProxy.h>
#include <vtkSmartPointer.h>
#include <vtkTable.h>

class ClientTableDisplay::implementation
{
public:
  implementation()
  {
  }

  ~implementation()
  {
    delete this->PropertyManager;
  }

  Ui::ClientTableDisplay Widgets;

  pqPropertyManager* PropertyManager;
  pqPropertyLinks Links;
};

ClientTableDisplay::ClientTableDisplay(pqRepresentation* representation, QWidget* p) :
  pqDisplayPanel(representation, p),
  Implementation(new implementation())
{
  this->Implementation->PropertyManager = new pqPropertyManager(this);

  vtkSMProxy* const proxy = vtkSMProxy::SafeDownCast(representation->getProxy());

  this->Implementation->Widgets.setupUi(this);
/*

  int attributeType = QString(vtkSMPropertyHelper(proxy, "AttributeType").GetAsString(3)).toInt();

  pqComboBoxDomain* d0 = new pqComboBoxDomain(
    this->Implementation->Widgets.attribute_mode, 
    proxy->GetProperty("AttributeType"),
    "field_list");
  d0->setObjectName("FieldModeDomain");

  vtkSMPropertyHelper(proxy, "AttributeType").Set(3, vtkVariant(attributeType).ToString());

  pqSignalAdaptorComboBox* adaptor = 
    new pqSignalAdaptorComboBox(this->Implementation->Widgets.attribute_mode);
  adaptor->setObjectName("ComboBoxAdaptor");

  this->Implementation->PropertyManager->registerLink(
    adaptor, 
    "currentText", 
    SIGNAL(currentTextChanged(const QString&)),
    proxy, 
    proxy->GetProperty("AttributeType"), 0); 

  this->Implementation->Links.addPropertyLink(
    adaptor,
    "currentText",
    SIGNAL(currentTextChanged(const QString&)),
    proxy,
    proxy->GetProperty("AttributeType"),0);

  QObject::connect(&this->Implementation->Links, SIGNAL(qtWidgetChanged()),
    this, SLOT(updateAllViews()));
  */

  vtkSMClientDeliveryRepresentationProxy* const repProxy = representation?
    vtkSMClientDeliveryRepresentationProxy::SafeDownCast(proxy) : NULL;
  repProxy->Update();

  proxy->UpdatePropertyInformation();

  pqSignalAdaptorSelectionTreeWidget* edgeFieldAdaptor = 
    new pqSignalAdaptorSelectionTreeWidget(this->Implementation->Widgets.columns, proxy->GetProperty("ColumnStatus"));
  edgeFieldAdaptor->setObjectName("SelectionTreeWidgetAdaptor1");

  this->Implementation->PropertyManager->registerLink(
    edgeFieldAdaptor, "values", SIGNAL(valuesChanged()),
    proxy, proxy->GetProperty("ColumnStatus"));

  this->Implementation->Links.addPropertyLink(
    edgeFieldAdaptor,
    "values",
    SIGNAL(valuesChanged()),
    proxy,
    proxy->GetProperty("ColumnStatus"));

  QObject::connect(&this->Implementation->Links, SIGNAL(qtWidgetChanged()),
    this, SLOT(updateAllViews()));
}

ClientTableDisplay::~ClientTableDisplay()
{
  delete this->Implementation;
}
