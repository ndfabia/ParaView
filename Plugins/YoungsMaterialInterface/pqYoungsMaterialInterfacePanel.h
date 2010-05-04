#ifndef __pqYoungsMaterialInterfacePanel
#define __pqYoungsMaterialInterfacePanel

#include "pqObjectPanel.h"

class pqYoungsMaterialInterfacePanel : public pqObjectPanel
{
  Q_OBJECT

  typedef pqObjectPanel Superclass;

public:
  pqYoungsMaterialInterfacePanel (pqProxy* proxy, QWidget* p);
  ~pqYoungsMaterialInterfacePanel ();

private slots:
  virtual void accept ();
  void setVolume (const QString&);
  void setNormal (const QString&);
  void setOrder (const QString&);
  void addMaterial ();
  void removeMaterial ();

private:
  class pqImplementation;
  pqImplementation* const Implementation;
};

#endif /* __pqYoungsMaterialInterfacePanel */

