//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH

#include <unordered_set>
#include <random>
#include <vector>
#include <string>

#include "../patient/patient.hh"
#include "name_generator.hh"
#include "gender_generator.hh"
#include "address_generator.hh"
#include "marital_status_generator.hh"
#include "language_generator.hh"
#include "telecom_generator.hh"
#include "identifier_generator.hh"
#include "multiple_birth_generator.hh"

using namespace std;

class generator {
public:
    static string generate_uuid() {
        static random_device dev;
        static mt19937 rng(dev());

        uniform_int_distribution<int> dist(0, 15);

        const char *v = "0123456789abcdef";
        const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

        string res;
        for (bool i : dash) {
            if (i) res += "-";
            res += v[dist(rng)];
            res += v[dist(rng)];
        }
        return res;
    }

    vector<patient> original_patients;

    class name_generator name_generator;
    class gender_generator gender_generator;
    class address_generator address_generator;
    class marital_status_generator marital_status_generator;
    class language_generator language_generator;
    class telecom_generator telecom_generator;
    class identifier_generator identifier_generator;
    class multiple_birth_generator multiple_birth_generator;

    explicit generator (vector<patient>& p) : original_patients(std::move(p)),
                                              name_generator(original_patients),
                                              gender_generator(original_patients),
                                              address_generator(original_patients),
                                              marital_status_generator(original_patients),
                                              language_generator(original_patients),
                                              telecom_generator(original_patients),
                                              identifier_generator(original_patients),
                                              multiple_birth_generator(original_patients) { }

    patient generate_patient () {
        string uuid = generate_uuid();
        gender gender = gender_generator.generate();
        name name = name_generator.generate(gender);
        address address = address_generator.generate();
        marital_status m_status = marital_status_generator.generate();
        vector<language> languages = language_generator.generate();

        return original_patients[0];
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH
