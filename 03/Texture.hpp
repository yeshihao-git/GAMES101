//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    // Eigen::Vector3f getColor(float u, float v)
    // {
    //     auto u_img = u * width;
    //     auto v_img = (1 - v) * height;
    //     auto color = image_data.at<cv::Vec3b>(v_img, u_img);
    //     return Eigen::Vector3f(color[0], color[1], color[2]);
    // }

    Eigen::Vector3f getColor(float u, float v)
    {
        // 限制纹理坐标u/v在[0,1]范围内（限制纹理坐标的安全范围）
        u = std::clamp(u, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        // 将[0,1]的u/v坐标转换为图片的像素坐标（浮点型）
        auto u_img = u * width;
        auto v_img = (1 - v) * height;

        // 像素坐标取整
        int x = static_cast<int>(u_img);
        int y = static_cast<int>(v_img);

        // 限制像素坐标在有效范围内
        x = std::clamp(x, 0, width - 1);
        y = std::clamp(y, 0, height - 1);

        // 从图片数据中采样颜色，转换为Eigen向量返回
        auto color = image_data.at<cv::Vec3b>(y, x);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
