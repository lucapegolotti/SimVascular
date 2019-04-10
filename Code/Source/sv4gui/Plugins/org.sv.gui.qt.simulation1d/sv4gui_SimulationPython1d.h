/* Copyright (c) Stanford University, The Regents of the University of
 *               California, and others.
 *
 * All Rights Reserved.
 *
 * See Copyright-SimVascular.txt for additional details.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// This class provides and interface to the generate-1d-mesh Python script 
// is used to generate a 1D mesh from centerlines geometry and create
// input files to the 1D solver. 
//
#ifndef SV4GUI_SIMULATION_PYTHON1D_H
#define SV4GUI_SIMULATION_PYTHON1D_H

#include <array>
#include <iostream>
#include <set>
#include <utility>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

class sv4guiSimulationPython1dParamNames
{ 
  public: 
    sv4guiSimulationPython1dParamNames() {
      allNames.insert(BOUNDARY_SURFACE_DIR);
      allNames.insert(CENTERLINE_INPUT_FILE);
      allNames.insert(COMPUTE_MESH);
      allNames.insert(MESH_OUTPUT_FILE);
      allNames.insert(OUTPUT_DIRECTORY);
      allNames.insert(WRITE_MESH_FILE);
    }
    const std::string BOUNDARY_SURFACE_DIR = "boundary_surfaces_directory";
    const std::string CENTERLINE_INPUT_FILE = "centerlines_input_file";
    const std::string COMPUTE_MESH = "compute_mesh";
    const std::string MESH_OUTPUT_FILE = "mesh_output_file";
    const std::string OUTPUT_DIRECTORY = "output_directory";
    const std::string WRITE_MESH_FILE = "write_mesh_file";
    std::set<std::string> allNames;
};

class sv4guiSimulationPython1d 
{
  public:
    sv4guiSimulationPython1d();
    ~sv4guiSimulationPython1d(); 
    bool GenerateMesh(const std::map<std::string, std::string>& params); 
    bool WriteMesh(const std::string fileName);
    std::string CreateCommand(const std::string infile, const std::string outfile);
    bool CheckParameters(const std::map<std::string, std::string>& params);
    bool WriteParameters(const std::string fileName, std::map<std::string, std::string>& params);

    std::string name; 
    std::string networkFileName; 
    vtkSmartPointer<vtkPolyData> meshPolyData;
    sv4guiSimulationPython1dParamNames parameterNames;
    std::map<std::string, std::string> parameterValues;
};

#endif //SV4GUI_SIMULATION_PYTHON1D_H
