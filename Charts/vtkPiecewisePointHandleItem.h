/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPiecewisePointHandleItem.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkPiecewisePointHandleItem - a vtkContextItem that draws handles
//       around a point of a piecewise function
//
// .SECTION Description
// This is a vtkContextItem that can be placed into a vtkContextScene. It draws
// handles around a given point of a piecewise function so that the curve can
// be adjusted using these handles.

#ifndef __vtkPiecewisePointHandleItem_h
#define __vtkPiecewisePointHandleItem_h

#include "vtkContextItem.h"
#include "vtkWeakPointer.h" // Needed for weak pointer to the PiecewiseFunction.

class vtkContext2D;
class vtkPiecewiseFunction;
class vtkCallbackCommand;
class vtkAbstractContextItem;

class VTK_CHARTS_EXPORT vtkPiecewisePointHandleItem : public vtkContextItem
{
public:
  vtkTypeMacro(vtkPiecewisePointHandleItem, vtkContextItem);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  static vtkPiecewisePointHandleItem *New();
  static void CallRedraw(vtkObject* sender, unsigned long event, void* receiver, void* params);

  // Description:
  // Set the parent item, which should be a vtkControlPointItem
  virtual void SetParent(vtkAbstractContextItem *parent);

  // Description:
  // Paint event for the item.
  virtual bool Paint(vtkContext2D *painter);

  // Description:
  // The current point id in the piecewise function being handled.
  vtkSetMacro(CurrentPointIndex, vtkIdType);
  vtkGetMacro(CurrentPointIndex, vtkIdType);

//BTX
  // Description
  // Set the PieceWiseFunction the handles will manipulate
  virtual void SetPiecewiseFunction(vtkPiecewiseFunction* piecewiseFunc);
  vtkWeakPointer<vtkPiecewiseFunction> GetPiecewiseFunction();

  // Description:
  // Returns the index of the handle if pos is over any of the handles,
  // otherwise return -1;
  int IsOverHandle(float* pos);

  // Description:
  // Returns true if the supplied x, y coordinate is inside the item.
  virtual bool Hit(const vtkContextMouseEvent &mouse);

  // Description:
  // Mouse enter event.
  //virtual bool MouseEnterEvent(const vtkContextMouseEvent &mouse);

  // Description:
  // Mouse move event.
  virtual bool MouseMoveEvent(const vtkContextMouseEvent &mouse);

  // Description:
  // Mouse leave event.
  //virtual bool MouseLeaveEvent(const vtkContextMouseEvent &mouse);

  // Description:
  // Mouse button down event.
  virtual bool MouseButtonPressEvent(const vtkContextMouseEvent &mouse);

  // Description:
  // Mouse button release event.
  virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);
//ETX

//BTX
protected:
  vtkPiecewisePointHandleItem();
  ~vtkPiecewisePointHandleItem();

  // Description:
  // Redraw all the handles
  virtual void Redraw();

  int MouseOverHandleIndex;
  vtkIdType CurrentPointIndex;
  float HandleRadius;

  vtkWeakPointer<vtkPiecewiseFunction> PiecewiseFunction;
  vtkCallbackCommand* Callback;

private:
  vtkPiecewisePointHandleItem(const vtkPiecewisePointHandleItem &); // Not implemented.
  void operator=(const vtkPiecewisePointHandleItem &);   // Not implemented.

  class InternalPiecewisePointHandleInfo;
  InternalPiecewisePointHandleInfo* Internal;
//ETX
};

#endif //__vtkPiecewisePointHandleItem_h
