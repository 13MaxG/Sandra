#include "operator.h"

Operator::Operator()
{
}

bool Operator::Add(Command *command)
{
    bool finded = false;


    //_arg_double
    for(std::list<OperatorItem< Argument<double> > >::iterator iter = _arg_double.begin(); iter != _arg_double.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            (*(*iter).object).Set( Key<double>(  fromString<double>((*command)[0]), fromString<double>((*command)[1]) ) );

        }
    }

    //_arg_int
    for(std::list<OperatorItem< Argument<int> > >::iterator iter = _arg_int.begin(); iter != _arg_int.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            (*(*iter).object).Set( Key<int>(  fromString<int>((*command)[0]), fromString<double>((*command)[1]) ) );
        }
    }

    //_arg_uint
    for(std::list<OperatorItem< Argument<unsigned int> > >::iterator iter = _arg_uint.begin(); iter != _arg_uint.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            (*(*iter).object).Set( Key<unsigned int>(  fromString<unsigned int>((*command)[0]), fromString<double>((*command)[1]) ) );
        }
    }

    // double
    for(std::list<OperatorItem<double> >::iterator iter = _double.begin(); iter != _double.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            *(*iter).object = fromString<double>((*command)[0]);
        }
    }

    // int
    for(std::list<OperatorItem<int> >::iterator iter = _int.begin(); iter != _int.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            *(*iter).object = fromString<int>((*command)[0]);
        }
    }

    // unsigned int
    for(std::list<OperatorItem<unsigned int> >::iterator iter = _uint.begin(); iter != _uint.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            *(*iter).object = fromString<unsigned int>((*command)[0]);
        }
    }

    // bool
    for(std::list<OperatorItem<bool> >::iterator iter = _bool.begin(); iter != _bool.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            *(*iter).object = ((*command)[0] == "true");
        }
    }

    // string
    for(std::list<OperatorItem<std::string> >::iterator iter = _string.begin(); iter != _string.end(); ++iter )
    {
        if((*iter).name == command->Name())
        {
            finded = true;

            *(*iter).object = (*command)[0];
        }
    }
    return finded;
}

void Operator::Register(std::string name, double* object)
{
    _double.push_back( OperatorItem<double>(object, name));
}

void Operator::Register(std::string name, int* object)
{
    _int.push_back( OperatorItem<int>(object, name));
}

void Operator::Register(std::string name, unsigned int* object)
{
    _uint.push_back( OperatorItem<unsigned int>(object, name));
}

void Operator::Register(std::string name, bool* object)
{
    _bool.push_back( OperatorItem<bool>(object, name));
}

void Operator::Register(std::string name, std::string* object)
{
    _string.push_back( OperatorItem<std::string>(object, name));
}


void Operator::Register(std::string name, Argument<double>* object)
{
    _arg_double.push_back( OperatorItem< Argument<double> >(object, name));
}

void Operator::Register(std::string name, Argument<int>* object)
{
    _arg_int.push_back( OperatorItem< Argument<int> >(object, name));
}

void Operator::Register(std::string name, Argument<unsigned int>* object)
{
    _arg_uint.push_back( OperatorItem< Argument<unsigned int> >(object, name));
}


void Operator::PrepareArgs()
{
    //_arg_double
    for(std::list<OperatorItem< Argument<double> > >::iterator iter = _arg_double.begin(); iter != _arg_double.end(); ++iter )
    {
        (*(*iter).object).Prepare();
    }

    //_arg_int
    for(std::list<OperatorItem< Argument<int> > >::iterator iter = _arg_int.begin(); iter != _arg_int.end(); ++iter )
    {
         (*(*iter).object).Prepare();
    }

    //_arg_uint
    for(std::list<OperatorItem< Argument<unsigned int> > >::iterator iter = _arg_uint.begin(); iter != _arg_uint.end(); ++iter )
    {
         (*(*iter).object).Prepare();
    }
}

void Operator::UpdateArgs( double dt)
{
    //_arg_double
    for(std::list<OperatorItem< Argument<double> > >::iterator iter = _arg_double.begin(); iter != _arg_double.end(); ++iter )
    {
        (*(*iter).object).Update(dt);
    }

    //_arg_int
    for(std::list<OperatorItem< Argument<int> > >::iterator iter = _arg_int.begin(); iter != _arg_int.end(); ++iter )
    {
         (*(*iter).object).Update(dt);
    }

    //_arg_uint
    for(std::list<OperatorItem< Argument<unsigned int> > >::iterator iter = _arg_uint.begin(); iter != _arg_uint.end(); ++iter )
    {
         (*(*iter).object).Update(dt);
    }
}
