#include "data_colector.cpp"

int main(){
    
    data_colector beta("LAB6_BIS_AL_S.ASC");
    vector<double> x = beta.get_a_certain_col(1);
    vector<double> y = beta.get_a_certain_col(2);

    /*vector<int> pos_to_erase;
    int counter = 0;

    for (int i = 0; i < y.size(); i++){
        
        if (y[i] != 0.00){
            
            y[i] = log10(y[i]);
        }

        else {

            pos_to_erase.push_back(i);
        }
    }

    for (int pos : pos_to_erase){

        x.erase(x.begin() + pos - counter);
        y.erase(y.begin() + pos - counter);

        counter += 1; 
    } LOG */

    double* x_ptr = &x[0];
    double* y_ptr = &y[0];
    Int_t points_numb = x.size();

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraph(points_numb, x_ptr, y_ptr);
    /*TF1* f1 = new TF1("f1", "gaus", 415, 431);
    TF1* f2 = new TF1("f2", "gaus", 431, 465.6);
    TF1* f3 = new TF1("f3", "gaus", 465.6, 575);*/
    //TPaveText* pt = new TPaveText(3.8, 500, 5.7, 900, "user");

    /*f1->SetParameter(0, 1 / ( 9.31 / 2.355 * sqrt(2 * M_PI)));
    f1->SetParameter(1, 421.81);
    f1->SetParameter(2, 9.31 / 2.355);
    f2->SetParameter(0, 1 / ( 9.25 / 2.355 * sqrt(2 * M_PI)));
    f2->SetParameter(1,  453.05);
    f2->SetParameter(2, 9.25 / 2.355);
    f3->SetParameter(0, 1 / ( 10.96 / 2.355 * sqrt(2 * M_PI)));
    f3->SetParameter(1, 477.59);
    f3->SetParameter(2, 10.96 / 2.355);*/
    
    /*pt->SetTextSize(0.032);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);*/
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);
    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 150);
    g->GetXaxis()->SetNdivisions(-515);

    /*g->GetXaxis()->SetLimits(0, 525);
    g->GetXaxis()->SetNdivisions(-521); LOG */

    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);
    g->GetYaxis()->SetTitle("Absolute frequency");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 1800);
    g->GetYaxis()->SetNdivisions(-418);

    /*g->GetYaxis()->SetRangeUser(0, 4.5);
    g->GetYaxis()->SetNdivisions(-509); LOG */
    
    /*f1->SetLineColor(kMagenta+2);
    f2->SetLineColor(kCyan);
    f3->SetLineColor(kRed-4);*/

    g->Draw("APL");
    /*g->Fit("f1", "R");
    g->Fit("f2", "R+");
    g->Fit("f3", "R+");*/
    /*pt->AddText(Form("y = (\\frac{a}{(r + c)^{2}}) (S.I.)"));
    pt->AddText(Form("a = (%.3f \\pm %.3f) (S.I.)", f->GetParameter(0), f->GetParError(0)));
    pt->AddText(Form("c = (%.4f \\pm %.4f) (S.I.)", f->GetParameter(1), f->GetParError(1)));
    pt->AddText(Form("\\chi^{2} = %.1f", f->GetChisquare()));*/
    //pt->Draw();

    C->Update();
    C->SaveAs("esp_BIS_AL.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    /*delete f1;
    delete f2;
    delete f3;*/
    //delete pt;
    delete A;

    return 0;
}