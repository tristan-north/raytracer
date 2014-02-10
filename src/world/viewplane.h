#ifndef VIEWPLANE_H
#define VIEWPLANE_H

class ViewPlane
{
public:
	int 			hres;   					// horizontal image resolution
	int 			vres;   					// vertical image resolution
	int				num_samples;				// number of samples per pixel

	float			gamma;						// gamma correction factor
	float			inv_gamma;					// the inverse of the gamma correction factor


	ViewPlane();									// default Constructor
	ViewPlane(const ViewPlane& vp);					// copy constructor
	ViewPlane& operator= (const ViewPlane& rhs);	// assignment operator
	~ViewPlane();									// destructor

	void set_hres(const int h_res);
	void set_vres(const int v_res);
	void set_gamma(const float g);
	void set_samples(const int n);
};


inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}

inline void ViewPlane::set_samples(const int n) {
	num_samples = n;
}

#endif // VIEWPLANE_H
