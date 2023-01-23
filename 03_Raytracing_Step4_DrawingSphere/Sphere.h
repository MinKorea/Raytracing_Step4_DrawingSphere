#pragma once

#include "Hit.h"
#include "Ray.h"

namespace hlab
{
    using namespace glm;

    class Sphere
    {
    public:
        glm::vec3 center;
        float radius;
        glm::vec3 color; // 뒤에서 '재질(material)'로 확장

        Sphere(const glm::vec3 &center, const float radius, const glm::vec3 &color)
            : center(center), color(color), radius(radius)
        {
        }

        // Wikipedia Line–sphere intersection
        // https://en.wikipedia.org/wiki/Line-sphere_intersection
        Hit IntersectRayCollision(Ray &ray)
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f)}; // d가 음수이면 충돌을 안한 것으로 가정

            /*
             * hit.d = ... // 광선의 시작점으로부터 충돌지점까지의 거리 (float)
             * hit.point = ... // 광선과 구가 충돌한 지점의 위치 (vec3)
             * hit.normal = .. // 충돌 지점에서 구의 단위 법선 벡터(unit normal vector)
             */

            const float dotSqaured1 = glm::dot(ray.dir, ray.start - center) * glm::dot(ray.dir, ray.start - center);
            const float nabla = 
                dotSqaured1 - (glm::distance(ray.start, center) * glm::distance(ray.start, center) - radius * radius);

            if (nabla > 0)
            {
                float d1 = -glm::dot(ray.dir, ray.start - center) + sqrt(nabla);
                float d2 = -glm::dot(ray.dir, ray.start - center) - sqrt(nabla);

                if (d1 < 0 || d2 < 0)   return hit;
                else
                {
                    hit.d = (d1 < d2) ? d1 : d2;
                    hit.point = ray.start + ray.dir * hit.d;
                    hit.normal = glm::normalize(hit.point - center);
                }
            }
            else if (nabla == 0)
            {
                hit.d = -glm::dot(ray.dir, ray.start - center);
                hit.point = ray.start + hit.d * ray.dir;
                hit.normal = glm::normalize(hit.point - center);
            }
            else return hit;



            // const float a = glm::dot(ray.dir, ray.dir); // dir이 unit vector라면 a는 1.0f라서 생략 가능

            return hit;
        } 
    };
}
