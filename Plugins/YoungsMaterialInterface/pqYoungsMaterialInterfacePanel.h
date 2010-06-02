#ifndef __pqYoungsMaterialInterfacePanel
#define __pqYoungsMaterialInterfacePanel

#include "pqObjectPanel.h"
#include <vtkstd/vector>
#include <vtkstd/string>

class pqYoungsMaterialInterfacePanel : public pqObjectPanel
{
  Q_OBJECT

  typedef pqObjectPanel Superclass;

public:
  pqYoungsMaterialInterfacePanel (pqProxy* proxy, QWidget* p);
  ~pqYoungsMaterialInterfacePanel ();

private slots:
  virtual void accept ();
  void addMaterial ();
  void removeMaterial ();

private:
  class pqImplementation;
  pqImplementation* const Implementation;
};

#endif /* __pqYoungsMaterialInterfacePanel */

