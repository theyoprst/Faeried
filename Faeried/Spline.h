#pragma once

#include <algorithm>
#include <vector>

inline float SplineInterpolation(float x1, float x2, float r1, float r2, float t)
{
	float res;
	float t2 = t*t;
	float t3 = t2*t;

	res = x1*(2.0f*t3 - 3.0f*t2 + 1.0f) + r1*(t3 - 2.0f*t2 + t) + x2*(-2.0f*t3 + 3.0f*t2) + r2*(t3 - t2);
	return res;
}

inline float GetGradient(float x1, float x2, float r1, float r2, float t)
{
	float res;
	float t2 = t*t;
	res = 6.0f*x1*(t2 - t) + r1*(3.0f*t2 - 4.0f*t + 1.0f) + 6.0f*x2*(t - t2) + r2*(3.0f*t2 - 2.0f*t);
	return res;
}

/*
	Класс SplinePath

	Класс для гладкой интерпляции Catmull-Rom сплайном

	Для использования необходимо сначала заполнить экземпляр класса ключевыми значениями
	вызовами addKey (передавая момент времени и значение ключа). После заполнения необходимо
	вызвать CalculateGradient для подсчета коэффицентов сплайна.

	После можно получить интерполированное значение между ключами вызовом getGlobalFrame(t),
	в качестве параметра методу передается нормированное время для интерполяции (таким образом
	t=0 соответствует первому ключу, а t=1 последнему).
*/

class SplinePath
{
public:

	typedef std::pair<float, float> KeyValue;

	struct KeyFrame
	{
		KeyValue value;
		float time;

		float td, ts;

		KeyFrame(float time_, float key)
			: value(key, key)
			, time(time_)
			, td(0.0f)
			, ts(0.0f)
		{}

		struct compare
		{
			bool operator() (const KeyFrame &a, const KeyFrame &b)
			{
				return a.time < b.time;
			}
		};

	};

	void clear() {
		keys.clear();
	}

	void addKey(const float time, float key) {
		keys.push_back(KeyFrame(time, key));
	}

	float getGlobalFrame(float t) {
		if (keys.empty()) {
			assert(false);
			// должен быть хотя бы один ключ
			return 0.0f;
		}

		if (keys.size() == 1) {
			return keys[0].value.first;
		}
		
		int tessSector = 0;
		for (size_t i = 0; i < (keys.size()-1); i++) {
			if (keys[i].time < t && keys[i+1].time >= t) {
				tessSector = (int)i;
				break;
			}            
		}

		float tessLocalTime = (t - keys[tessSector].time) / (keys[tessSector+1].time - keys[tessSector].time);
		return getFrame(tessSector, tessLocalTime);
	}

	float getGlobalGradient(float t) {
		if (keys.empty()) {
			assert(false);
			// должен быть хотя бы один ключ
			return 0.0f;
		}

		if (keys.size() == 1) {
			return 0.0f;
		}

		int tessSector = 0;
		for (size_t i = 0; i < (keys.size()-1); i++) {
			if (keys[i].time < t && keys[i+1].time >= t) {
				tessSector = (int)i;
				break;
			}            
		}

		float tessLocalTime = (t - keys[tessSector].time) / (keys[tessSector+1].time - keys[tessSector].time);
		return getGradient(tessSector, tessLocalTime);
	}

	int getSectors() {
		return static_cast<int>(keys.size()-1);
	}

	void CalculateGradient() {
		std::sort(keys.begin(), keys.end(), KeyFrame::compare());

		keys[0].ts = 0.5f*(keys[1].value.first-keys[0].value.first);
		float dd = keys[1].time-keys[0].time;
		keys[0].ts = (keys[0].ts*dd);

		size_t e = keys.size()-1;
		keys[e].td = 0.5f*(keys[e].value.first-keys[e-1].value.first);
		dd = keys[e].time-keys[e-1].time;
		keys[e].td = (keys[e].td*dd);

		for (size_t i = 1; i < (keys.size()-1); i++) {
			keys[i].td = 0.5f*(keys[i+1].value.first-keys[i].value.first)+
				0.5f*(keys[i].value.first-keys[i-1].value.first);

			keys[i].ts = keys[i].td;

			int in = (int)i;
			float dd = (keys[in].time-keys[in-1].time) + (keys[in+1].time-keys[in].time);
			float k1 = 2.0f*(keys[in].time-keys[in-1].time)/dd;
			float k2 = 2.0f*(keys[in+1].time-keys[in].time)/dd;

			keys[i].td = k1*keys[i].td;
			keys[i].ts = k2*keys[i].ts;

		}
	}

private:

	std::vector<KeyFrame> keys;

	float getFrame(int sector, float t) {
		size_t i = static_cast<size_t>(sector);
		return SplineInterpolation(keys[i].value.first, keys[i+1].value.first, keys[i].ts, keys[i+1].td, t);
	}

	float getGradient(int sector, float t) {
		size_t i = static_cast<size_t>(sector);
		return GetGradient(keys[i].value.first, keys[i+1].value.first, keys[i].ts, keys[i+1].td, t);
	}


};