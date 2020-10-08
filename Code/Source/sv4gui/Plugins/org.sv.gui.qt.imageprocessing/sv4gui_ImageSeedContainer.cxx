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

#include "sv4gui_ImageSeedContainer.h"
#include "math.h"
#include <tuple>

//--------------------------
// sv4guiImageSeedContainer
//--------------------------
//
sv4guiImageSeedContainer::sv4guiImageSeedContainer()
{
  m_ActiveStartSeedID = -1;
  m_CurrentStartSeedID = -1;
  m_CurrentEndSeedID = -1;
  //m_startSeeds = std::vector<std::vector<double>>();
  //m_endSeeds = std::vector<std::vector<std::vector<double>>>();
  hoverPoint.push_back(0.0);
  hoverPoint.push_back(0.0);
  hoverPoint.push_back(0.0);
  selectStartSeed = false;
  selectStartSeedIndex = -1;
  selectEndSeed = false;
  selectEndSeedIndex = -1;
};

sv4guiImageSeedContainer::sv4guiImageSeedContainer(const sv4guiImageSeedContainer& other) :BaseData(other)
{
  for (auto const& seed : other.m_StartSeeds) {
      auto startSeed = std::get<0>(seed.second);
      auto point = startSeed.point;
      AddStartSeed(point[0], point[1], point[2]);
      for (auto const& endSeed : std::get<1>(seed.second)) {
          auto point = endSeed.point;
          AddEndSeed(point[0], point[1], point[2]);
      }
  }
}

sv4guiImageSeedContainer::~sv4guiImageSeedContainer()
{
}

//--------------------
// SetActiveStartSeed
//--------------------
//
void sv4guiImageSeedContainer::SetActiveStartSeed(int seedID)
{
  try {
      auto seed = m_StartSeeds.at(seedID);
      m_ActiveStartSeedID = seedID;
  } catch (...) {
      std::cout << "[SetActiveStartSeed] **** Internal error: invalid start seed ID: " << seedID << std::endl;
  }

}

//--------------
// AddStartSeed
//--------------
// Add a start seed.
//
void sv4guiImageSeedContainer::AddStartSeed(double x, double y, double z)
{
  //std::cout << "========== sv4guiImageSeedContainer::AddStartSeed ========== " << std::endl;
  m_CurrentStartSeedID += 1;
  int id = m_CurrentStartSeedID;
  //std::cout << "[AddStartSeed] m_CurrentStartSeedID: " << m_CurrentStartSeedID << std::endl;
  auto startSeed = std::make_tuple(sv4guiImageSeed(id, id, x, y, z), std::vector<sv4guiImageSeed>()); 
  m_StartSeeds.insert(std::pair<int,sv4guiImageStartSeed>(id, startSeed));
  m_ActiveStartSeedID = id;
};

//------------
// AddEndSeed
//------------
// Add an end seed to the currently active start seed.
//
void sv4guiImageSeedContainer::AddEndSeed(double x, double y, double z)
{
  std::cout << "========== sv4guiImageSeedContainer::AddEndSeed ========== " << std::endl;
  if (m_ActiveStartSeedID == -1) {
    return;
  }
  //std::cout << "[AddEndSeed] m_ActiveStartSeedID: " << m_ActiveStartSeedID << std::endl;
  int startID = m_ActiveStartSeedID;
  m_CurrentEndSeedID += 1;
  int endID = m_CurrentEndSeedID;

  auto seed = m_StartSeeds.find(startID);
  if (seed == m_StartSeeds.end()) {
    std::cout << "[AddEndSeed] **** Internal error: m_ActiveStartSeedID " << m_ActiveStartSeedID << " is not valid." << std::endl;
    return;
  }
  auto startSeed = std::get<0>(seed->second); 
  std::get<1>(seed->second).emplace_back(sv4guiImageSeed(startID, endID, x, y, z)); 
}

//------------------
// GetNumStartSeeds
//------------------
//
int sv4guiImageSeedContainer::GetNumStartSeeds() const 
{
  return m_StartSeeds.size();
}

//----------------
// GetNumEndSeeds
//----------------
//
int sv4guiImageSeedContainer::GetNumEndSeeds(int startSeedIndex) const 
{
  try {
      auto seed = m_StartSeeds.at(startSeedIndex);
      return std::get<1>(seed).size();
  } catch (...) {
      std::cout << "[GetNumEndSeeds] **** Internal error: : startSeedIndex " << startSeedIndex << std::endl;
  }

  return 0;
}

//--------------
// GetStartSeed
//--------------
//
std::array<double,3> 
sv4guiImageSeedContainer::GetStartSeed(int seedIndex) const 
{
  try {
      auto seed = m_StartSeeds.at(seedIndex);
      return std::get<0>(seed).point;
  } catch (...) {
      std::cout << "[GetStartSeed] **** Internal error: : seedIndex: " << seedIndex << std::endl;
  }

  return std::array<double,3> {0,0,0};
}

//--------------
// GetStartSeed
//--------------
//
std::array<double,3> 
sv4guiImageSeedContainer::GetEndSeed(int startSeedIndex, int endSeedIndex) const
{
  std::array<double,3> point;

  try {
      auto seed = m_StartSeeds.at(startSeedIndex);
      auto endSeeds = std::get<1>(seed);
      for (auto const& endSeed : endSeeds) { 
          if (endSeedIndex == endSeed.id) {
              point = endSeed.point;
              break;
          }
      }

  } catch (...) {
      std::cout << "[GetEndSeed] **** Internal error: startSeedIndex: " << startSeedIndex << std::endl;
  }

  return point; 
}

//-----------------
// FindNearestSeed
//-----------------
// Find the seed within 'tol' of the given point.
//
// If the nearest seed is a start seed then return its ID in 'startID' and
// and return -1 for 'endID'.
//
// If the nearest seed is an end seed then return its ID in 'endID' and
// the start node it is associated with in 'startID'.
//
void sv4guiImageSeedContainer::FindNearestSeed(double x, double y, double z, double tol, int& startID, int& endID)
{
  startID = -1;
  endID = -1;

  int numStartSeeds = GetNumStartSeeds();
  if (numStartSeeds == 0) {
      return;
  }

  // Search seed points.
  //
  for (auto const& seed : m_StartSeeds) {
      auto startSeed = std::get<0>(seed.second);
      auto point = startSeed.point;
      auto d = Distance(point[0], point[1], point[2], x, y ,z);
      if (d <= tol) {
          startID = startSeed.id;
          return;
      }
      for (auto const& endSeed : std::get<1>(seed.second)) {
          auto point = endSeed.point;
          auto d = Distance(point[0], point[1], point[2], x, y, z);
          if (d <= tol){
              startID = startSeed.id;
              endID = endSeed.id;
              return;
          }
      }
  }
}

//------------
// ClearSeeds
//------------
// Delete all seeds.
//
void sv4guiImageSeedContainer::ClearSeeds()
{
  std::cout << "========== sv4guiImageSeedContainer::ClearSeeds ========== " << std::endl;
  m_StartSeeds.clear();
}

//------------
// DeleteSeed
//------------
// Remove a start or end seed.
//
void sv4guiImageSeedContainer::DeleteSeed(int startIndex, int endIndex)
{
  #ifdef dbg_sv4guiImageSeedContainer_DeleteSeed
  std::cout << "========== sv4guiImageSeedContainer::DeleteSeed ========== " << std::endl;
  std::cout << "[DeleteSeed] startIndex: " << startIndex << std::endl;
  std::cout << "[DeleteSeed] endIndex: " << endIndex << std::endl;
  #endif

  auto seed = m_StartSeeds.find(startIndex);
  if (seed == m_StartSeeds.end()) {
    std::cout << "[DeleteSeed] **** Internal error: startIndex " << startIndex << " is not valid." << std::endl;
    return;
  }

  // Remove all end seeds and the given start seed.
  //
  if (endIndex == -1) {
      auto startSeed = std::get<0>(seed->second); 
      std::get<1>(seed->second).clear();
      m_StartSeeds.erase(seed);

      // Reset the active seed.
      m_ActiveStartSeedID = -1;
      for (auto const& seed : m_StartSeeds) {
          m_ActiveStartSeedID = seed.first;
          break;
      }

  // Remove a single end seed from the given start seed.
  //
  } else {
      auto startSeed = std::get<0>(seed->second); 
      int index = 0;
      for (auto const& endSeed : std::get<1>(seed->second)) {
          if (endSeed.id == endIndex) {
              break;
          }
          index += 1;
      }
      std::get<1>(seed->second).erase(std::get<1>(seed->second).begin()+index);
  }

  return;
}

//----------
// Distance
//----------
// Compute the distance between two points.
//
double 
sv4guiImageSeedContainer::Distance(double x1, double y1, double z1, double x2, double y2, double z2) const 
{
  auto d1 = (x1-x2)*(x1-x2);
  auto d2 = (y1-y2)*(y1-y2);
  auto d3 = (z1-z2)*(z1-z2);
  return sqrt(d1+d2+d3);
}

