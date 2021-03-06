#include "HiggsAnalysis/HiggsToTauTau/interface/PlotLimits.h"

void 
PlotLimits::print(const char* filename, std::string& xval, std::string& yval, std::vector<TGraph*> contour, const char* type)
{
  if(std::string(type) == std::string("tex")){
    ofstream file;
    file.open (std::string(filename).append(".tex").c_str());
    file
      << "   " << std::setw(15) << std::right << xval << " (pb) " 
      << " & " << std::setw(15) << std::right << yval << " (pb) "
      << std::right << "  \\\\"
      << std::endl << "\\hline" << std::endl;
    for(std::vector<TGraph*>::const_iterator g=contour.begin(); g!=contour.end(); ++g){
      unsigned int precision = 5;
      for(int idx=0; idx<(*g)->GetN(); ++idx){
	file
	  << "   " << std::setw(15) << std::fixed << std::scientific << std::setprecision(precision) << std::right << (*g)->GetX()[idx]
	  << " & " << std::setw(15) << std::fixed << std::scientific << std::setprecision(precision) << std::right << (*g)->GetY()[idx]
	  << std::right << "  \\\\"
	  << std::endl << "\\hline" << std::endl;
      }
    }
  }
  if(std::string(type) == std::string("txt")){
    ofstream file;
    file.open (std::string(filename).append(".txt").c_str());
    file
      << "   " << std::setw(15) << std::right << xval 
      << "   " << std::setw(15) << std::right << yval
      << std::endl;
    for(std::vector<TGraph*>::const_iterator g=contour.begin(); g!=contour.end(); ++g){
      unsigned int precision = 5;
      for(int idx=0; idx<(*g)->GetN(); ++idx){
	file
	  << "   " << std::setw(15) << std::fixed << std::scientific << std::setprecision(precision) << std::right << (*g)->GetX()[idx]
	  << "   " << std::setw(15) << std::fixed << std::scientific << std::setprecision(precision) << std::right << (*g)->GetY()[idx]
	  << std::endl;
      }
    }
  }
}

void
PlotLimits::print(const char* filename, TGraphAsymmErrors* outerBand, TGraphAsymmErrors* innerBand, TGraph* expected, TGraph* observed, const char* type)
{
  if(std::string(type) == std::string("tex")){
    ofstream file;
    file.open (std::string(filename).append(".tex").c_str());
    file
      << "   " << std::setw(15) << std::right << "    $m_{\\mathrm H}$";
    if(outerBand){
      file
	<< " & " << std::setw(15) << std::right << "$-2\\sigma$";
    }
    file
      << " & " << std::setw(15) << std::right << "$-1\\sigma$"
      << " & " << std::setw(15) << std::right << "     Median"
      << " & " << std::setw(15) << std::right << "$+1\\sigma$";
    if(outerBand){
      file
	<< " & " << std::setw(15) << std::right << "$+2\\sigma$";
    }
    file
      << " & " << std::setw(15) << std::right << "Obs. Limit"
      << std::right << "  \\\\"
      << std::endl << "\\hline" << std::endl;
    unsigned int precision = 3;
    for(int imass=0; imass<expected->GetN(); ++imass){
      file
	<< "   " << std::setw(15) << std::setprecision(3) << std::resetiosflags(std::ios_base::fixed) << std::right << expected->GetX()[imass] << "~\\GeV";
      if(outerBand){
	double value = expected->GetY()[imass] - outerBand->GetEYlow()[imass];
	int exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
        double coeff = value/TMath::Power(10., exponent);
	if(exponent>=0){
	  file
	    << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << value;
	}
	else{
	  file
	    << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
	}
      }
      double value = expected->GetY()[imass] - innerBand->GetEYlow()[imass];
      int exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
      double coeff = value/TMath::Power(10., exponent);
      if(exponent>=0){
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << value;
      }
      else{
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
      }
      value =  expected->GetY()[imass];
      exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
      coeff = value/TMath::Power(10., exponent);
      if(exponent>=0){
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << value;
      }
      else{
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
      }
      value = expected->GetY()[imass] + innerBand->GetEYhigh()[imass];;
      exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
      coeff = value/TMath::Power(10., exponent);
      if(exponent>=0){
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << value;
      }
      else{
	file
	  << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
      }
      if(outerBand){	
	double value = expected->GetY()[imass] - outerBand->GetEYlow()[imass];
	int exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
        double coeff = value/TMath::Power(10., exponent);
	if(exponent>=0){
	  file
	    << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << value;
	}
	else{
	  file
	    << " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
	}
      }
      if(observed){
	double value = observed->GetY()[imass];
	int exponent = TMath::Nint(TMath::Floor(TMath::Log10(value)));
        double coeff = value/TMath::Power(10., exponent);
	if(exponent>=0){
	  file
	    << " & " << std::setw(15) << std::right << value;
	}
	else{
	  file
	    << " & " << std::setw(15) << std::right << coeff << " \\cdot 10^{" << exponent << "}";
	}
      }
      file
	<< std::right << "  \\\\"
	<< std::endl << "\\hline" << std::endl;
    }
    file.close();
  }
  if(std::string(type) == std::string("txt")){
    ofstream file;
    file.open (std::string(filename).append(".txt").c_str());
    file
      << "#"
      << "   " << std::setw(15) << std::right << "         mX";
    if(outerBand){
      file
	<< "   " << std::setw(15) << std::right << "   -2 sigma";
    }
    file
      << "   " << std::setw(15) << std::right << "   -1 sigma"
      << "   " << std::setw(15) << std::right << "     Median"
      << "   " << std::setw(15) << std::right << "   +1 sigma";
    if(outerBand){
      file
	<< "   " << std::setw(15) << std::right << "   +2 sigma";
    }
    file
      << "   " << std::setw(15) << std::right << "Obs. Limit [pb]"
      << std::endl;
    for(int imass=0; imass<expected->GetN(); ++imass){
      file
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetX()[imass];
      if(outerBand){
	file
	  << "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass] - outerBand->GetEYlow()[imass];
      }
      file
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass] - innerBand->GetEYlow()[imass]
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass]
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass] + innerBand->GetEYhigh()[imass];
      if(outerBand){
	file
	  << "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass] + outerBand->GetEYhigh()[imass];
      }
      if(observed){
	file
	  << "   " << std::setw(15) << std::right << observed->GetY()[imass];
      }
      file
	<< std::endl;
    }
    file.close();
  }
}

void
PlotLimits::print(const char* filename, TGraph* expected, TGraph* observed, const char* type)
{
  if(std::string(type) == std::string("tex")){
    ofstream file;
    file.open (std::string(filename).append(".tex").c_str());
    file
      << "   " << std::setw(15) << std::right << "    $m_{\\mathrm H}$"
      << " & " << std::setw(15) << std::right << "$-2\\sigma$"
      << " & " << std::setw(15) << std::right << "$-1\\sigma$"
      << " & " << std::setw(15) << std::right << "     Median"
      << " & " << std::setw(15) << std::right << "$+1\\sigma$"
      << " & " << std::setw(15) << std::right << "$+2\\sigma$"
      << " & " << std::setw(15) << std::right << "Obs. Limit"
      << std::right << "  \\\\"
      << std::endl << "\\hline" << std::endl;
    unsigned int precision = 2;
    for(int imass=0; imass<expected->GetN(); ++imass){
      file
	<< "   " << std::setw(15) << std::setprecision(3) << std::resetiosflags(std::ios_base::fixed) << std::right << expected->GetX()[imass] << "~\\GeV"
	<< " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << " - "
	<< " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << " - "
	<< " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << expected->GetY()[imass]
	<< " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << " - "
	<< " & " << std::setw(15) << std::fixed << std::setprecision(precision) << std::right << " - ";
      if(observed){
	file
	  << " & " << std::setw(15) << std::right << observed->GetY()[imass];
      }
      file
	<< std::right << "  \\\\"
	<< std::endl << "\\hline" << std::endl;
    }
    file.close();
  }
  if(std::string(type) == std::string("txt")){
    ofstream file;
    file.open (std::string(filename).append(".txt").c_str());
    file
      << "#"
      << "   " << std::setw(15) << std::right << "         mX"
      << "   " << std::setw(15) << std::right << "   -2 sigma"
      << "   " << std::setw(15) << std::right << "   -1 sigma"
      << "   " << std::setw(15) << std::right << "     Median"
      << "   " << std::setw(15) << std::right << "   +1 sigma"
      << "   " << std::setw(15) << std::right << "   +2 sigma"
      << "   " << std::setw(15) << std::right << "Obs. Limit [pb]"
      << std::endl;
    for(int imass=0; imass<expected->GetN(); ++imass){
      file
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetX()[imass]
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << " - "
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << " - "
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << expected->GetY()[imass]
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << " - "
	<< "   " << std::setw(15) << std::setprecision(3) << std::right << " - ";
      if(observed){
	file
	  << "   " << std::setw(15) << std::right << observed->GetY()[imass];
      }
      file
	<< std::endl;
    }
    file.close();
  }
}

