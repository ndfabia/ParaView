#include "pqYoungsMaterialInterfacePanel.h"

#include "ui_pqYoungsMaterialInterfacePanel.h"

#include "vtkSMArrayListDomain.h"
#include "vtkSMProxy.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMStringVectorProperty.h"

#include <pqProxy.h>

class pqYoungsMaterialInterfacePanel::pqImplementation 
{
public:
  Ui::YoungsMaterialInterfacePanel UI;
};

//-----------------------------------------------------------------------------
pqYoungsMaterialInterfacePanel::pqYoungsMaterialInterfacePanel (pqProxy* object_proxy, QWidget* p) :
  Superclass (object_proxy, p),
  Implementation (new pqImplementation())
{
  this->Implementation->UI.setupUi (this);

  QObject::connect (
    this->Implementation->UI.addMaterial, SIGNAL(clicked()),
    this, SLOT(addMaterial()));
  QObject::connect (
    this->Implementation->UI.removeMaterial, SIGNAL(clicked()),
    this, SLOT(removeMaterial()));

  vtkSMStringVectorProperty *myProp;
  myProp = vtkSMStringVectorProperty::SafeDownCast (this->proxy()->GetProperty ("Material"));
  vtkSMArrayListDomain *volumes = vtkSMArrayListDomain::SafeDownCast (myProp->GetDomain ("scalar_list"));
  for (unsigned i = 0; i < volumes->GetNumberOfStrings (); i ++)
    {
    this->Implementation->UI.volumeArray->addItem (volumes->GetString(i));
    }
  vtkSMArrayListDomain *normals = vtkSMArrayListDomain::SafeDownCast (myProp->GetDomain ("vector_list"));
  for (unsigned i = 0; i < normals->GetNumberOfStrings (); i ++)
    {
    this->Implementation->UI.normalArray->addItem (normals->GetString(i));
    }
  vtkSMArrayListDomain *orders = vtkSMArrayListDomain::SafeDownCast (myProp->GetDomain ("scalar_list"));
  for (unsigned i = 0; i < orders->GetNumberOfStrings (); i ++)
    {
    this->Implementation->UI.orderArray->addItem (orders->GetString(i));
    }

}

pqYoungsMaterialInterfacePanel::~pqYoungsMaterialInterfacePanel ()
{
  delete this->Implementation;
}

void pqYoungsMaterialInterfacePanel::accept ()
{
  vtkSMProxy* const proxy = this->referenceProxy()->getProxy();

  int val = this->Implementation->UI.onionPeel->checkState() == Qt::Checked;
  vtkSMPropertyHelper (proxy, "OnionPeel").Set (val);
  val = this->Implementation->UI.axisSymmetric->checkState() == Qt::Checked;
  vtkSMPropertyHelper (proxy, "AxisSymetric").Set (val);
  val = this->Implementation->UI.fillMaterial->checkState() == Qt::Checked;
  vtkSMPropertyHelper (proxy, "FillMaterial").Set (val);

  int count = this->Implementation->UI.materials->rowCount ();
  vtkSMPropertyHelper (proxy, "NumberOfMaterials").Set (count);
  for (int i = 0; i < count; i ++)
    {
    QString volume = this->Implementation->UI.materials->item(i, 0)->text ();
    QString normal = this->Implementation->UI.materials->item(i, 1)->text ();
    QString order = this->Implementation->UI.materials->item(i, 2)->text ();
    vtkSMPropertyHelper (proxy, "Material").Set (i*4+0, i);
    vtkSMPropertyHelper (proxy, "Material").Set (i*4+1, volume.toAscii().constData());
    vtkSMPropertyHelper (proxy, "Material").Set (i*4+2, normal.toAscii().constData());
    vtkSMPropertyHelper (proxy, "Material").Set (i*4+3, order.toAscii().constData());
    }

  proxy->UpdateVTKObjects ();
  Superclass::accept ();
}

void pqYoungsMaterialInterfacePanel::addMaterial ()
{
  int count = this->Implementation->UI.materials->rowCount ();
  this->Implementation->UI.materials->setRowCount( count + 1 );

  QString volume = this->Implementation->UI.volumeArray->currentText();
  QString normal = this->Implementation->UI.normalArray->currentText();
  QString order = this->Implementation->UI.orderArray->currentText();

  this->Implementation->UI.materials->setItem(count, 0, new QTableWidgetItem (volume));
  this->Implementation->UI.materials->setItem(count, 1, new QTableWidgetItem (normal));
  this->Implementation->UI.materials->setItem(count, 2, new QTableWidgetItem (order));
  this->Implementation->UI.materials->resizeRowToContents(count);
}

void pqYoungsMaterialInterfacePanel::removeMaterial ()
{
  QList<QTableWidgetItem *> list = this->Implementation->UI.materials->selectedItems ();
  if (list.length () > 0) 
    {
    int selectedRow = this->Implementation->UI.materials->row (list.first ());
    this->Implementation->UI.materials->removeRow (selectedRow);
    }
}
