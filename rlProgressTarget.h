#pragma once

class rlProgressTarget
{
	public:
		rlProgressTarget (void);
		virtual ~rlProgressTarget (void);

		virtual void OnSetRange (const int, const int);
		virtual void OnSetPosition (const int);

};
