/*******************************************************************************
 * Copyright (c) 2015 Chris Satterwhite
 * Copyright (c) 2018 David D. Marshall <ddmarsha@calpoly.edu>
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * See LICENSE.md file in the project root for full license information.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Chris Satterwhite - initial code and implementation
 *    David D. Marshall - misc. changes
 ******************************************************************************/

#ifndef __CPanel___Unstructured_Panel_Code__cpNode__
#define __CPanel___Unstructured_Panel_Code__cpNode__

#include <stdio.h>
#include <Eigen/Dense>
#include <vector>

class edge;
class bodyPanel;


class cpNode
{
	using edges_type = std::vector<edge *>;
	using edges_index_type = edges_type::size_type;
	using bodyPanels_type = std::vector<bodyPanel *>;
	using bodyPanels_index_type = bodyPanels_type::size_type;

    Eigen::Vector3d pnt;
    size_t index;
    edges_type edges;
    bodyPanels_type bodyPans;
    double c_w = 1.3; //vpp
    
    bool TEnode;

	// lin
	Eigen::Vector3d linCPnormal;
	//double CPoffset = 0.0000001; // Scales normal
	//double linCPoffset = 1.0e-7;
	double linCPoffset = 1.0e-10;
	//double linCPoffset = 1.0e-3;

	double linDoubletStrength = 0;
	double linPotential = 0;
	double linPrevPotential = 0;
	Eigen::Vector3d linVelocity = Eigen::Vector3d::Zero();
    
public:
    cpNode(Eigen::Vector3d pnt,size_t iindex);
        
    Eigen::Vector3d operator-=(const cpNode &rhs);
    
    Eigen::Vector3d operator+=(const cpNode &rhs);
    
    void addEdge(edge* e);
    void addBodyPanel(bodyPanel* p);
    
    edge* getTE(edge* exception);
    
    void setTE();
    void setIndex(size_t i);
    
    void setPnt(Eigen::Vector3d pos){pnt = pos;}
    Eigen::Vector3d getPnt() const {return pnt;}
    
    size_t getIndex() const {return index;}
    
    std::vector<edge*> getEdges() {return edges;}
    
    std::vector<bodyPanel*> getBodyPans() {return bodyPans;}
    
    edge* getOtherTrailEdge(edge* current);
    std::vector<edge*> getTrailingEdges();
    
    Eigen::Vector3d nodeWakeProjAngle();
    Eigen::Vector3d firstProjNode(double dt, double inputV);
    Eigen::Vector3d secProjNode(double dt, double inputV);
    
    bool isTE() {return TEnode;}

	// lin
	void setLinCPnormal();
	Eigen::Vector3d calcCP();
	void linSetMu(double linDubStrength);
	void linSetPotential(Eigen::Vector3d Vinf);
	void linSetVelocity(Eigen::Vector3d Vel);

	double linGetMu() { return linDoubletStrength; }
	double linGetPotential() { return linPotential; }
    
};

#endif /* defined(__CPanel___Unstructured_Panel_Code__cpNode__) */
