#include <rad_trig.c>

float CycleMeasure(vars Price){
	var Imult = .635;
	var Qmult = .338;
	vars InPhase = series(0);
	vars Quadrature = series(0);
	vars Phase = series(0);
	vars DeltaPhase = series(0);
	vars InstPeriod = series(0);
	vars Period = series(0);
	vars Value3 = series(0);


	if (Bar > 5) {
		Value3[0] = Price[0] - Price[7]; // 7 ?
		InPhase[0] = 1.25*(Value3[4] - Imult*Value3[2]) + Imult*InPhase[3];
		Quadrature[0] = Value3[2] - Qmult*Value3[0] + Qmult*Quadrature[2];

		if (abs(InPhase[0]+InPhase[1]) > 0){
			Phase[0] = ratan(
				abs(
					(Quadrature[0]+Quadrature[1]) / 
					(InPhase[0]+InPhase[1])
				)
			);
		}

		if (InPhase[0] < 0 && Quadrature[0] > 0) {
			Phase[0] = 180 - Phase[0];
		}

		if (InPhase[0] < 0 && Quadrature[0] < 0) {
			Phase[0] = 180 + Phase[0];
		}

		if (InPhase[0] > 0 && Quadrature[0] < 0) {
			Phase[0] = 360 - Phase[0];
		}

		DeltaPhase[0] = Phase[1] - Phase[0];

		if (Phase[1] < 90 && Phase[0] > 270) {
			DeltaPhase[0] = 360 + Phase[1] - Phase[0];
		}

		if (DeltaPhase[0] < 1) {
			DeltaPhase[0] = 1;
		}

		if (DeltaPhase[0] > 60) {
			DeltaPhase[0] = 60;
		}

		InstPeriod[0] = 0;
		var Value4 = 0;

		int count = 0;
		for (count = 0; count < 50; count++) {
			Value4 = Value4 + DeltaPhase[count];
			if (Value4 > 360 && InstPeriod[0] == 0) {
				InstPeriod[0] = count;
			}
		}
	}

	if (InstPeriod[0] == 0) {
		InstPeriod[0] = InstPeriod[1];
	}

	Period[0] = .25*(InstPeriod[0]) + .75*Period[1];
	return Period[0];
}
