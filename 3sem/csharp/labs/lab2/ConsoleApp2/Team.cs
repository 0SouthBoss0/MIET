using System;

namespace ConsoleApp2
{
    class Team : INameAndCopy
    {
        protected string organization;
        protected int regnumber;

        public Team(string organization, int regnumber)
        {
            this.organization = organization;
            this.regnumber = regnumber;
        }

        public Team()
        {
            organization = "Организация";
            regnumber = 0;
        }

        public string Organization
        {
            get { return organization; }
            set { organization = value; }
        }

        public int Regnumber
        {
            get { return regnumber; }
            set
            {
                if (value <= 0)
                {
                    throw new NegativeRegNumber("Регистрационный номер некорректный!");
                }
                regnumber = value;
            }
        }

        // реализация интерфейса INameAndCopy
        public virtual string Name
        {
            get { return String.Format("Номер: {0}, Организация: {1}", regnumber, organization); }
            set => throw new NotImplementedException();
        }

        // реализация интерфейса INameAndCopy
        public virtual object DeepCopy()
        {
            return new Team(organization, regnumber);
        }

        // переопределение виртуального метода bool Equals
        public override bool Equals(object obj)
        {
            if (obj == null)
            {
                return false;
            }

            Team objAsTeam = obj as Team;
            ;
            if (objAsTeam as Team == null)
            {
                return false;
            }

            return objAsTeam.organization == this.organization && objAsTeam.regnumber == this.regnumber;

        }

        // определение операции ==
        public static bool operator ==(Team obj1, Team obj2)
        {
            return obj1.Equals(obj2);
        }

        // определение операции !=
        public static bool operator !=(Team obj1, Team obj2)
        {
            return !(obj1 == obj2);

        }

        // переопредение виртуального метода int GetHashCode()
        public override int GetHashCode()
        {
            return organization.GetHashCode() + regnumber.GetHashCode();
        }

        // переопределение виртуального метода string ToString()
        public override string ToString()
        {
            return Name;
        }

    }

}
