#pragma once

class rlFrequency
{
	public:
		enum FrequencyUnits
		{
			unknown	= 0,
			Hz		= 1,
			KHz		= 2,
			MHz		= 3,
			GHz		= 4,
		};

	public:
		rlFrequency (const double = 0, const rlFrequency::FrequencyUnits = Hz);
		~rlFrequency (void);

		rlFrequency::FrequencyUnits GetDefaultUnits (void);
		void SetDefaultUnits (const rlFrequency::FrequencyUnits DefaultUnits);

		double GetFrequency (void) const;
		double GetFrequencyHz (void) const;
		double GetFrequencyKHz (void) const;
		double GetFrequencyMHz (void) const;
		double GetFrequencyGHz (void) const;

		void SetFrequency (const double dfFrequency);
		void SetFrequencyHz (const double dfFrequencyHz);
		void SetFrequencyKHz (const double dfFrequencyKHz);
		void SetFrequencyMHz (const double dfFrequencyMHz);
		void SetFrequencyGHz (const double dfFrequencyGHz);

		rlFrequency &operator= (double);

	protected:
		double m_dfFrequencyHz;
		rlFrequency::FrequencyUnits m_DefaultUnits;

};
