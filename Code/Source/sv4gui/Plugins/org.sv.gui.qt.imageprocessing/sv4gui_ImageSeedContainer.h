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

// The sv4guiImageSeedContainer class is used to store data for the seed points node.
//
// The seed points node is created in sv4guiImageProcessing::CreateQtPartControl(). 
//
#ifndef SV4GUI_IMAGE_SEED_CONTAINER_H
#define SV4GUI_IMAGE_SEED_CONTAINER_H

#include <array>
#include <iostream>
#include <map>
#include <vector>
#include "mitkBaseData.h"

//-----------------
// sv4guiImageSeed
//-----------------
// The sv4guiImageSeed class stores data for a seed position.
//
class sv4guiImageSeed {
  public:
    sv4guiImageSeed(int startID, int id, double x, double y, double z) : startID(startID), id(id), point({x,y,z}) {
    };
    sv4guiImageSeed(const sv4guiImageSeed &seed) {
      id = seed.id;
      startID = seed.startID;
      point = seed.point;
    };
    ~sv4guiImageSeed() { 
    };
    int startID;
    int id;
    std::array<double,3> point;
}; 

//----------------------
// sv4guiImageStartSeed
//----------------------
// The sv4guiImageStartSeed tuple stores data for a start seed.
//
typedef std::tuple<sv4guiImageSeed, std::vector<sv4guiImageSeed>> sv4guiImageStartSeed;
typedef std::tuple<int,int> sv4guiImageSeedID;

//--------------------------
// sv4guiImageSeedContainer
//--------------------------
//
class sv4guiImageSeedContainer : public mitk::BaseData 
{
  public:
    mitkClassMacro(sv4guiImageSeedContainer, mitk::BaseData);
    itkFactorylessNewMacro(Self)
    itkCloneMacro(Self)

    void AddStartSeed(double x, double y, double z);
    void AddEndSeed(double x, double y, double z);
    int GetNumStartSeeds() const;
    int GetNumEndSeeds(int startSeedIndex) const;
    std::array<double,3> GetStartSeed(int seedIndex) const;
    std::array<double,3> GetEndSeed(int startSeedIndex, int endSeedIndex) const;
    void FindNearestSeed(double x, double y, double z, double tol, int& startID, int& endId);
    void DeleteSeed(int startIndex, int endIndex);
    double Distance(double x1,double y1,double z1,double x2,double y2,double z2) const;
    void ClearSeeds();

    void SetActiveStartSeed(int seedID);

    //virtual methods, that need to be implemented due to mitk::BaseData inheriting
    //from itk::DataObject
    //however if we dont intend to use this object with an itk filter we can leave them
    //empty
    virtual void UpdateOutputInformation() {};
    virtual void SetRequestedRegionToLargestPossibleRegion() {};
    virtual bool RequestedRegionIsOutsideOfTheBufferedRegion() { return false;};
    virtual bool VerifyRequestedRegion() { return true;};
    virtual void SetRequestedRegion(const itk::DataObject *data) {};

    std::vector<double> hoverPoint = std::vector<double>();
    bool selectStartSeed;
    int selectStartSeedIndex;
    bool selectEndSeed;
    int selectEndSeedIndex;

    int m_CurrentEndSeedID;
    int m_CurrentStartSeedID;
    int m_ActiveStartSeedID;
    std::map<int,sv4guiImageStartSeed> m_StartSeeds;

  protected:

    mitkCloneMacro(Self);
    sv4guiImageSeedContainer();
    sv4guiImageSeedContainer(const sv4guiImageSeedContainer& other);
    virtual ~sv4guiImageSeedContainer();

  private:
    // std::vector< std::vector<double> > m_startSeeds;
    // std::vector< std::vector< std::vector<double> > > m_endSeeds;
};

#endif 
