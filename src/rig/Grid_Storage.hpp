#ifndef GRID_STORAGE__HPP_
#define GRID_STORAGE__HPP_

#include "axom/spin.hpp"
#include "axom/core.hpp"
#include "axom/primal.hpp"

#include <vector>

class GridStorage {
public:
    using ImpGrid2d = axom::spin::ImplicitGrid_Accel<in2D>;
    using BBox2d = axom::primal::BoundingBox<double, in2D>;
    using Tri2d = axom::primal::Triangle<double, in2D>;
    using Point2d = axom::primal::Point<double, in2D>;
    using ImpGrid3d = axom::spin::ImplicitGrid_Accel<in3D>;
    using BBox3d = axom::primal::BoundingBox<double, in3D>;
    using Tri3d = axom::primal::Triangle<double, in3D>;
    using Point3d = axom::primal::Point<double, in3D>;
    
    GridStorage(int bmax, int objcount, int cellcount, int dim){
        dimcount = dim;
        if(dim == 2){
            double extents[2] = {bmax, bmax};
            double eytents[2] = {bmax, bmax};
            int real_res[2] = {bmax/cellcount, bmax/cellcount};
            2d_stor = ImpGrid2d(extents, eytents, real_res, objcount);
            
        }
        else if(dim == 3){
            double extents[3] = {bmax, bmax, bmax};
            double eytents[3] = {bmax, bmax, bmax};
            int real_res[3] = {bmax/cellcount, bmax/cellcount, bmax/cellcount};
            3d_stor = ImpGrid3d(extents, eytents, real_res, objcount);
        }

    }

    

private:
    ImpGrid2d 2d_stor;
    ImpGrid3d 3d_stor;
    int dimcount;

    std::vector<BBox3d> 3d_bstor;
    std::vector<BBox2d> 2d_bstor;

    std::vector<Tri2d> 2d_tstor;
    std::vector<Tri3d> 3d_tstor;
}; 

#endif 
