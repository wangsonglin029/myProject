#include "kalman.h"
#include "math.h"
#include "mdefine.h"

/*
  状态估计的方差包括噪音的方差、模型预测值的方差和预测值相对真实值的偏差的平方
*/

/* 
  初始化卡尔曼滤波器,Q R 的值，也可能会受到其他的参数影响，R 的数值越大收敛越慢，鲁棒性越好
  R 为负值时，表示估计值大于测量值，R 为正数时，表示估计值比测量值小，在 SOC 虚高时 R 用正值，在
  SOC 实低时 R 用负值
*/

/*
  在卡尔曼滤波中，系统噪声和测量噪声对结果都会产生影响。系统噪声是指在真实系统中存在的无法预知的噪声，
  而测量噪声是指在传感器测量过程中产生的噪声。系统噪声的大小会影响到卡尔曼滤波器对系统状态的预测。
  如果系统噪声较大，卡尔曼滤波器会更多地依赖测量值来进行状态估计，而忽略了对系统状态的先验知识。
  这样会导致估计结果更加接近测量值，但也会增加估计误差。测量噪声的大小会影响到卡尔曼滤波器对测量值的权重分配。
  如果测量噪声较大，卡尔曼滤波器会更加相信系统模型的预测，而忽略测量值。这样会导致估计结果更加平滑，
  但也会延迟对系统状态变化的响应。因此，系统噪声和测量噪声都会对卡尔曼滤波器的估计结果产生影响，过大或过小
  的噪声都会导致估计结果的不准确性。
*/

/*
  方差值为0.01与0.1和1之间有以下区别：
  方差值为0.01表示数据的扩散程度较小，数据点相对集中在均值附近，变异性较小。
  方差值为0.1表示数据的扩散程度适中，数据点在均值附近呈现较为均匀的分布。
  方差值为1表示数据的扩散程度较大，数据点相对分散，变异性较大。
*/

/* 用于解决电流测量误差 */
KalmanFilter kf_current;

/* 用于解决 SOC 系统误差 */
KalmanFilter kf_soc;

void kalman_filter_init(KalmanFilter *kf, float X0, float P0, float R)
{
  kf -> X = X0;    // 状态估计，循环迭代
  kf -> P = P0;    // 状态估计的方差，循环迭代
  kf -> A = 1;     // 状态转移矩阵，模型决定
  kf -> H = 1;     // 观测矩阵，模型决定
  kf -> Q = 0.01;  // 系统噪声协方差，先验，根据测试中的值计算 / 根据计算结果估计
  kf -> R = R;     // 测量噪声协方差，先验，根据测试中的值计算 / 根据计算结果估计
}

// 卡尔曼滤波器预测步骤
void kalman_filter_predict(KalmanFilter *kf)
{
  // 状态预测
  kf -> X = kf -> A * kf -> X;
  
  // 方差预测
  kf -> P = kf -> A * kf -> P * kf -> A + kf -> Q;
}

// 卡尔曼滤波器更新步骤
void kalman_filter_update(KalmanFilter *kf, float z)
{
  // 计算卡尔曼增益
  float K = kf -> P * kf -> H / (kf -> H * kf -> P * kf -> H + kf -> R);
  
  // 更新状态估计
  kf -> X = kf -> X + K * (z - kf -> H * kf -> X);
  
  // 更新方差估计
  kf -> P = (1 - K * kf -> H) * kf -> P;
}

/* 电流突变情况下设置合适的状态变量以使其更快速的收敛 */
void kalman_filter_x_update(KalmanFilter *kf, float x)
{
  kf -> X = x;
}

// 放在循环中，循环迭代
float KalmanFliter(KalmanFilter *kf, float Measurement_Value)
{
  float Estimate_Value;
  kalman_filter_predict(kf);                               // 预测步骤
  kalman_filter_update(kf, Measurement_Value);             // 更新步骤
  Estimate_Value = kf -> X;                                // 得到估计值
  return Estimate_Value;
}

/* 电流的卡尔曼滤波初始化 */
void CurrentKalmanFliterInit(void)
{
  kalman_filter_init(&kf_current, 0, 1, 10);
}

/* Soc 的卡尔曼滤波初始化 */
void SocKalmanFliterInit(float R)
{
  kalman_filter_init(&kf_soc, 0, 1, R);
}

/* 电流卡尔曼滤波 */ 
float CurrentKalmanFliter(float Measurement_Value)
{
  float Current_Estimate = KalmanFliter(&kf_current, Measurement_Value);
  // printf("\r\nCurrent_Measurement:%f,Current_Estimate:%f\r\n",Measurement_Value, Current_Estimate);
  return Current_Estimate;
}

/* Soc 卡尔曼滤波 */ 
float SocKalmanFliter(float Measurement_Value)
{
  float Soc_Estimate = KalmanFliter(&kf_soc, Measurement_Value);
  // printf("\r\nSoc_Measurement:%f,Soc_Estimate:%f\r\n",Measurement_Value, Soc_Estimate);
  return Soc_Estimate;
}

/*
 估计值将变小
 y = -4E-07x3 + 1E-05x2 - 0.002x - 0.0022
 R2 = 0.9996

 y = [0, 0.09],  soc 调整范围：[-1，-32]
*/
float GetPositiveRvalue(uint8_t x)
{
#if 0
  float y0 = 4.0 * pow(10, -7) * pow(x, 3);
  float y1 = 1.0 * pow(10, -5) * pow(x, 2);
  float y2 = 0.002 * x;
  float y = y0 + y1 + y2 - 0.0021;
  return y;
  
#else
  union
  {
    float rf;
    uint32_t r32;
  }Rn;
  
  uint32_t *pointer = (uint32_t*)WRITE_KALMAN_ADDR;
  Rn.r32 = pointer[x];
  return Rn.rf;
#endif
  
}

/*
 估计值将变小
 y = 8E-08x3 - 2E-05x2 + 0.002x + 0.0023 
 R2 = 0.999],  soc 调整范围：[-1，80]

 y = [-0.06, 0]
*/
float GetNegativeRvalue(uint8_t x)
{
#if 0
  float y0 = -8 * pow(10,-8) * pow(x,3);
  float y1 =  2 * pow(10,-5) * pow(x,2);
  float y2 = -0.002 * x;
  float y = y0 + y1 + y2 - 0.0023;
  return y;
  
#else
  union
  {
    float rf;
    uint32_t r32;
  }Rn;
  
  uint32_t *pointer = (uint32_t*)WRITE_KALMAN_ADDR;
  Rn.r32 = pointer[x + 50];
  return Rn.rf;
#endif
  
}

// Kalman 测试
void Kalman_Test(void)
{
	uint8_t estimate[101] = {0};
	uint8_t measure = 0;
	
  SocKalmanFliterInit(1.0);

  for(measure = 1; measure <= 100; measure ++)
  {
    estimate[measure] = SocKalmanFliter(measure);
  }
  
  if(estimate[100] == 0)return;
}















