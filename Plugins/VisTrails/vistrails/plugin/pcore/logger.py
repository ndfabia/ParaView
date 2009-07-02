
############################################################################
##
## This file is part of the Vistrails ParaView Plugin.
##
## This file may be used under the terms of the GNU General Public
## License version 2.0 as published by the Free Software Foundation
## and appearing in the file LICENSE.GPL included in the packaging of
## this file.  Please review the following to ensure GNU General Public
## Licensing requirements will be met:
## http://www.opensource.org/licenses/gpl-2.0.php
##
## This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
## WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
############################################################################

############################################################################
##
## Copyright (C) 2006, 2007, 2008 University of Utah. All rights reserved.
## Copyright (C) 2008, 2009 VisTrails, Inc. All rights reserved.
##
############################################################################

import CaptureAPI
import sys, traceback, string

class VistrailsLogger(object):
    """
    """
    def __init__(self):
        pass

    def write(self, text):
        """
        write(text: string) -> None
        """
        CaptureAPI.printApp(text)

    def flush(self):
        pass
        
def VistrailsExceptHook(type, value, tb):
    sys.__excepthook__(type, value, tb)
    lines = traceback.format_exception(type, value, tb)
    CaptureAPI.printApp(string.join(lines))

    
# Direct output to Application window    
sys.stdout = VistrailsLogger()
sys.stderr = VistrailsLogger()
#sys.excepthook = VistrailsExceptHook