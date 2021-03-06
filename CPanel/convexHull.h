/*******************************************************************************
 * Copyright (c) 2014 Chris Satterwhite
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

#ifndef __CPanel__convexHull__
#define __CPanel__convexHull__

#include <stdio.h>
#include <Eigen/Dense>
#include <vector>
#include <list>
#include <algorithm>
#include "math.h"
#include "cpNode.h"


class convexHull
{
    struct member
    {
        member(const Eigen::Vector3d &point, const Eigen::Vector3d &basePnt);
        double x,y,z,theta,d;
    };
    struct compareTheta
    {
        inline bool operator()(member* p1, member* p2)
        {
            return (p1->theta < p2->theta);
        }
    };
    struct compareDistAscending
    {
        inline bool operator()(member* p1, member* p2)
        {
            return (p1->d < p2->d);
        }
    };
    struct compareDistDescending
    {
        inline bool operator()(member* p1, member* p2)
        {
            return (p1->d > p2->d);
        }
    };

    using members_type = std::vector<member *>;
    using members_index_type = members_type::size_type;

    members_type members;
    members_type hull;

    void computeHull();
    bool boundary;
    // TRUE : Points on boundary consider inside hull and therefore not included in hull vector.
    // FALSE : Points on boundary considered outside of hull and therefore included in hull vector

    Eigen::Vector3d makeVector(member* p1, member* p2);

public:

    convexHull(Eigen::MatrixXd points, bool boundary);
    ~convexHull()
    {
        for (members_index_type i = 0; i<members.size(); i++)
        {
            delete members[i];
        }
    }
    std::vector<member*> getHull() {return hull;}

    bool compareNodes(std::vector<Eigen::Vector3d> nodesLocal);
};

#endif /* defined(__CPanel__convexHull__) */
