#include "axom/spin.hpp"
#include "axom/core.hpp"
#include "axom/primal.hpp"

class GridStorage {
    using ImpGrid2d = axom::spin::ImplicitGrid_Accel<in2D>;
    using BBox2d = axom::primal::BoundingBox<double, in2D>;
    using Tri2d = axom::primal::Triangle<double, in2D>;
    using Point2d = axom::primal::Point<double, in2D>;
    using ImpGrid3d = axom::spin::ImplicitGrid_Accel<in3D>;
    using BBox3d = axom::primal::BoundingBox<double, in3D>;
    using Tri3d = axom::primal::Triangle<double, in3D>;
    using Point3d = axom::primal::Point<double, in3D>;
} 
