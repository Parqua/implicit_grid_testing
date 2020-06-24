#ifndef GRID_STORAGE__HPP_
#define GRID_STORAGE__HPP_

#include <iostream>
#include <cmath>
#include "axom/spin.hpp"
#include "axom/core.hpp"
#include "axom/primal.hpp"
#include "axom/slam.hpp"

#include <vector>

constexpr int in3D = 3;
constexpr int in2D = 2;
using ImpGrid2d = axom::spin::ImplicitGrid<in2D>;
using BBox2d = axom::primal::BoundingBox<double, in2D>;
using Tri2d = axom::primal::Triangle<double, in2D>;
using Point2d = axom::primal::Point<double, in2D>;
using ImpGrid3d = axom::spin::ImplicitGrid<in3D>;
using BBox3d = axom::primal::BoundingBox<double, in3D>;
using Tri3d = axom::primal::Triangle<double, in3D>;
using Point3d = axom::primal::Point<double, in3D>;
using BitSet = axom::slam::BitSet;
using namespace axom::utilities;

class GridStorage {
    public:

        GridStorage(double bmax, int objcount, int cellcount, int dim){
            dimcount = dim;
            m_size=bmax;

            if(dim == 2){
                objcount *= objcount;               
                double mins[2] = {0, 0};
                double maxes[2] = {bmax, bmax};
                int real_res[2] = {cellcount, cellcount};
                two_stor = ImpGrid2d(mins, maxes, real_res, objcount);
                genTriangles2d(objcount, bmax);
                genBboxes2d();
                for(int i =0; i<two_bstor.size(); i++){
                    two_stor.insert(two_bstor[i], i);
                }   

            }
            else if(dim == 3){
                objcount*= objcount * objcount;
                double mins[3] = {0, 0, 0};
                double maxes[3] = {bmax, bmax, bmax};
                int real_res[3] = {cellcount, cellcount, cellcount};
                three_stor = ImpGrid3d(mins, maxes, real_res, objcount);
                genTriangles3d(objcount, bmax);
                genBboxes3d();
                for(int i =0; i<three_bstor.size(); i++){
                    printf("Inserting:");
                    three_bstor[i].print(std::cout);
                    three_stor.insert(three_bstor[i], i);
                }   


            }

        }


        void basic3dTest(){
            BBox3d tester;
            Point3d p[2];
            //p[0] = Point3d::make_point(random_real(8.0, m_size/2), random_real(0.0, m_size/2), random_real(0.0, m_size/2));
            //p[1] = Point3d::make_point(random_real(m_size/2, m_size), random_real(m_size/2, m_size), random_real(m_size/2, m_size));
            p[0] = Point3d::make_point(0, 0, 0);
            p[1] = Point3d::make_point(10, 10, 10);
            //Current 3d tester is this point.    
            Point3d ptest = Point3d::make_point(4, 2, 6);
            tester.addPoint(p[0]);
            tester.addPoint(p[1]);
            
            BitSet b = three_stor.getCandidates(ptest);
            int idx = b.find_first();
            printf("%d\n", idx); 
            while((idx =b.find_next(idx)) != BitSet::npos){
                printf("%d\n", idx); 
            }          
        }
        void basic2dTest(){

        }
    private:

        void genTriangles2d(int tricount, double bmax){
            Point2d p[3];
            double size_per_tri = bmax/(tricount*2);
            for(int i = 0; i < sqrt(tricount); i++){
                for(int j = 0; j < sqrt(tricount); j++){
                    p[0] = Point2d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri));
                    p[1] = Point2d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri));
                    p[2] = Point2d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri)); 

                    Tri2d t(p[0], p[1], p[2]);
                    two_tstor.push_back(t);

                }
            }
        }

        inline BBox2d findBbox(Tri2d tri){
            BBox2d bbox;
            bbox.addPoint(tri[0]);
            bbox.addPoint(tri[1]);
            bbox.addPoint(tri[2]); 
            return bbox;
        }

        void genBboxes2d(){
            for(int i = 0; i < two_tstor.size(); i++){
                two_bstor.push_back(findBbox(two_tstor[i]));
            }        

        }



        inline BBox3d findBbox(Tri3d tri){
            BBox3d bbox;

            bbox.addPoint(tri[0]);
            bbox.addPoint(tri[1]);
            bbox.addPoint(tri[2]); 
            return bbox;
        }

        void genBboxes3d(){
            for(int i = 0; i < three_tstor.size(); i++){
                three_bstor.push_back(findBbox(three_tstor[i]));
            }        

        }
        void genTriangles3d(int tricount, double bmax){
            Point3d p[3];
            double size_per_tri = bmax/cbrt(tricount);
/*
            for(int i = 0; i < (int)cbrt(tricount); i++){
                for(int j = 0; j < (int)cbrt(tricount); j++){
                    for(int k = 0; k < (int)cbrt(tricount); k++){
                        p[0] = Point3d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri),random_real(k*size_per_tri,(1+k)*size_per_tri));
                        p[1] = Point3d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri),random_real(k*size_per_tri,(1+k)*size_per_tri));
                        p[2] = Point3d::make_point(random_real(i*size_per_tri, (1+i)*size_per_tri),random_real(j*size_per_tri,(1+j)*size_per_tri),random_real(k*size_per_tri,(1+k)*size_per_tri)); 
                        Tri3d t(p[0], p[1], p[2]);
                        three_tstor.push_back(t);
                    }
                }
            }
*/
        p[0] = Point3d::make_point(70, 70, 70);
        p[1] = Point3d::make_point(80,70,70);
        p[2] = Point3d::make_point(90, 80, 90);
        Tri3d t(p[0], p[1], p[2]);
        three_tstor.push_back(t);
        }
    private:
        ImpGrid2d two_stor;
        ImpGrid3d three_stor;
        int dimcount;
        double m_size;


        std::vector<BBox3d> three_bstor;
        std::vector<BBox2d> two_bstor;

        std::vector<Tri2d> two_tstor;
        std::vector<Tri3d> three_tstor;
}; 

#endif 
