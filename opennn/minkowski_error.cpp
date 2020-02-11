//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   M I N K O W S K I   E R R O R   C L A S S                             
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "minkowski_error.h"

namespace OpenNN
{

/// Default constructor. 
/// It creates Minkowski error term not associated to any neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.

MinkowskiError::MinkowskiError() : LossIndex()
{
   set_default();
}


/// Neural network constructor. 
/// It creates a Minkowski error term associated to a neural network but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.

MinkowskiError::MinkowskiError(NeuralNetwork* new_neural_network_pointer)
: LossIndex(new_neural_network_pointer)
{
   set_default();
}


/// Data set constructor. 
/// It creates a Minkowski error term not associated to any neural network but to be measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.

MinkowskiError::MinkowskiError(DataSet* new_data_set_pointer)
: LossIndex(new_data_set_pointer)
{
   set_default();
}


/// Neural network and data set constructor. 
/// It creates a Minkowski error term object associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

MinkowskiError::MinkowskiError(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
 : LossIndex(new_neural_network_pointer, new_data_set_pointer)
{
   set_default();
}


/// XML constructor. 
/// It creates a Minkowski error object neither associated to a neural network nor to a data set. 
/// The object members are loaded by means of a XML document.
/// @param mean_squared_error_document TinyXML document with the Minkowski error elements.

MinkowskiError::MinkowskiError(const tinyxml2::XMLDocument& mean_squared_error_document)
 : LossIndex(mean_squared_error_document)
{
   set_default();

   from_XML(mean_squared_error_document);
}


/// Destructor.
/// It does not delete any pointer.

MinkowskiError::~MinkowskiError() 
{
}


/// Returns the Minkowski exponent value used to calculate the error. 

type MinkowskiError::get_Minkowski_parameter() const
{
   return minkowski_parameter;
}


/// Sets the default values to a Minkowski error object:
/// <ul>
/// <li> Minkowski parameter: 1.5.
/// <li> Display: true.
/// </ul>

void MinkowskiError::set_default()
{
   minkowski_parameter = 1.5;

   display = true;
}


/// Sets a new Minkowski exponent value to be used in order to calculate the error. 
/// The Minkowski R-value must be comprised between 1 and 2. 
/// @param new_Minkowski_parameter Minkowski exponent value. 

void MinkowskiError::set_Minkowski_parameter(const type& new_Minkowski_parameter)
{
   // Control sentence

   if(new_Minkowski_parameter < static_cast<Index>(1.0) || new_Minkowski_parameter > static_cast<type>(2.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Error. MinkowskiError class.\n"
             << "void set_Minkowski_parameter(const type&) method.\n"
             << "The Minkowski parameter must be comprised between 1 and 2.\n";
    
      throw logic_error(buffer.str());
   }

   // Set Minkowski parameter
  
   minkowski_parameter = new_Minkowski_parameter;
}


/// Returns a string with the name of the Minkowski error loss type, "MINKOWSKI_ERROR".

string MinkowskiError::get_error_type() const
{
   return "MINKOWSKI_ERROR";
}


/// Returns a string with the name of the Minkowski error loss type in text format.

string MinkowskiError::get_error_type_text() const
{
   return "Minkowski error";
}


/// Serializes the Minkowski error object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this document-> 

tinyxml2::XMLDocument* MinkowskiError::to_XML() const
{
   ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   // Minkowski error

   tinyxml2::XMLElement* Minkowski_error_element = document->NewElement("MinkowskiError");

   document->InsertFirstChild(Minkowski_error_element);

   // Minkowski parameter
   {
      tinyxml2::XMLElement* Minkowski_parameter_element = document->NewElement("MinkowskiParameter");
      Minkowski_error_element->LinkEndChild(Minkowski_parameter_element);

      buffer.str("");
      buffer << minkowski_parameter;

      tinyxml2::XMLText* Minkowski_parameter_text = document->NewText(buffer.str().c_str());
      Minkowski_parameter_element->LinkEndChild(Minkowski_parameter_text);
   }

   // Display
//   {
//      tinyxml2::XMLElement* display_element = document->NewElement("Display");
//      Minkowski_error_element->LinkEndChild(display_element);

//      buffer.str("");
//      buffer << display;

//      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
//      display_element->LinkEndChild(display_text);
//   }

   return document;
}


/// Serializes the cross entropy error object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document

void MinkowskiError::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    ostringstream buffer;

    // Error type

    file_stream.OpenElement("Error");

    file_stream.PushAttribute("Type", "MINKOWSKI_ERROR");

    // Minkowski parameter

    file_stream.OpenElement("MinkowskiParameter");

    buffer.str("");
    buffer << minkowski_parameter;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Close error

    file_stream.CloseElement();

    // Regularization

    write_regularization_XML(file_stream);
}


/// Loads a Minkowski error object from a XML document.
/// @param document TinyXML document containing the members of the object.

void MinkowskiError::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("MinkowskiError");

    if(!root_element)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: MinkowskiError class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Minkowski error element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Minkowski parameter

     const tinyxml2::XMLElement* error_element = root_element->FirstChildElement("Error");

     if(error_element)
     {
        const tinyxml2::XMLElement* parameter_element = error_element->FirstChildElement("MinkowskiParameter");

        const type new_Minkowski_parameter = static_cast<type>(atof(parameter_element->GetText()));

        try
        {
           set_Minkowski_parameter(new_Minkowski_parameter);
        }
        catch(const logic_error& e)
        {
           cerr << e.what() << endl;
        }
     }

     // Regularization

     tinyxml2::XMLDocument regularization_document;
     tinyxml2::XMLNode* element_clone;

     const tinyxml2::XMLElement* regularization_element = root_element->FirstChildElement("Regularization");

     element_clone = regularization_element->DeepClone(&regularization_document);

     regularization_document.InsertFirstChild(element_clone);

     regularization_from_XML(regularization_document);

//  // Display
//  {
//     const tinyxml2::XMLElement* display_element = root_element->FirstChildElement("Display");

//     if(display_element)
//     {
//        const string new_display_string = display_element->GetText();

//        try
//        {
//           set_display(new_display_string != "0");
//        }
//        catch(const logic_error& e)
//        {
//           cerr << e.what() << endl;
//        }
//     }
//  }
}

type MinkowskiError::minkowski_error(const Tensor<type, 2>& x, const Tensor<type, 2>& y, const type& minkowski_parameter) const
{
    const Index rows_number = x.dimension(0);
    const Index columns_number = x.dimension(1);

#ifdef __OPENNN_DEBUG__

    const Index other_rows_number = y.dimension(0);

    if(other_rows_number != rows_number)
    {
       ostringstream buffer;

       buffer << "OpenNN Exception: Metrics functions.\n"
              << "type minkowski_error(const Tensor<type, 2>&, const Tensor<type, 2>&, const type&) method.\n"
              << "Other number of rows " << other_rows_number << " must be equal to this number of rows " << rows_number << ".\n";

       throw logic_error(buffer.str());
    }

    const Index other_columns_number = y.dimension(1);

    if(other_columns_number != columns_number)
    {
       ostringstream buffer;

       buffer << "OpenNN Exception: Metrics functions.\n"
              << "type minkowski_error(const Tensor<type, 2>&, const Tensor<type, 2>&, const type&) method.\n"
              << "Other number of columns (" << other_columns_number << ") must be equal to this number of columns (" << columns_number << ").\n";

       throw logic_error(buffer.str());
    }

    #endif
/*
    type minkowski_error = static_cast<type>(0.0);
    type row_minkowski_error = static_cast<type>(0.0);
*/
    Tensor<type, 0> error = (((x - y).abs().pow(minkowski_parameter)).sum()).pow(static_cast<type>(1.0)/ minkowski_parameter);

    return error(0);
/*
    for(Index i = 0; i < rows_number; i++)
    {
        row_minkowski_error = static_cast<type>(0.0);

        for(Index j = 0; j < columns_number; j++)
        {
            row_minkowski_error += pow(abs(x(i,j) - y(i,j)), minkowski_parameter);
        }

        minkowski_error += pow(row_minkowski_error, static_cast<type>(1.0) / minkowski_parameter);
    }

    return minkowski_error;
*/
}
}


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
