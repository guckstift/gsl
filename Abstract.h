#pragma once

struct Abstract {
	Abstract* type;
};

void AbstractInit (Abstract* abs, Abstract* type);
